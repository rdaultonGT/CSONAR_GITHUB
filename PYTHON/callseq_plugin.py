#
#      Copyright (c) 2017, an unpublished work by GrammaTech, Inc.
#                      ALL RIGHTS RESERVED
# 
#      This software is furnished under a license and may be used and
#      copied only in accordance with the terms of such license and the
#      inclusion of the above copyright notice.  This software or any
#      other copies thereof may not be provided or otherwise made
#      available to any other person.  Title to and ownership of the
#      software is retained by GrammaTech, Inc.
#

# Assume you have a program that defines these procedures:
# 
# void openParen(void){putchar( '(' );}
# void closeParen(void){putchar( ')' );}
# void openBracket(void){putchar( '[' );}
# void closeBracket(void){putchar( ']' );}
# 
# This plugin will check that all strings output by this program
# (assuming these are the only calls to putchar) have properly
# balanced parenthesis and brackets.
# 
# The check is intraprocedural.  It is subject to false negatives in
# the presence of loops and conditions that cause resource limits to
# expire.  It is subject to false positives in the presence of
# some interprocedural transfer of parenthesis ownership.
# 
# Example:
# void foo(){ int i = rand(); 
#             if( i ) openParen(); else openBracket(); 
#             if( i ) closeParen(); else closeBracket(); 
# }
# This procedure can output the strings:
# '()' and '[]'
# 
# These strings are well-formed:
# []
# ()
# []()([])
# 
# These strings are not well-formed:
# [)
# (]
# [[]
# )
# [(])

import cs

missing_open_wc = cs.analysis.create_warningclass(
    'Missing open',
    '',
    1.0,
    cs.warningclass_flags.NONE,
    cs.warning_significance.STYLE)  
 
missing_close_wc = cs.analysis.create_warningclass(
    'Missing close',
    '',
    2.0,
    cs.warningclass_flags.NONE,
    cs.warning_significance.STYLE)  
 
mismatched_wc = cs.analysis.create_warningclass(
    'Mismatched close',
    '',
    1.0,
    cs.warningclass_flags.NONE,
    cs.warning_significance.STYLE)  

# A helper function. Given a point p and a string fname,
# return True if p is a call site where fname is called,
# False otherwise. 
def point_calls_function(p, fname):
    try:
        pcallee = p.callee()
    except cs.result, r:
        if r != cs.result.ERROR_NOT_A_CALL_SITE:
            raise
        return False    
    if pcallee and pcallee.name()==fname:
        return True
    return False


class paren_state(cs.step_state):
    # Define __init__ to set up the initial state
    def __init__(self):
        super(paren_state,self).__init__()
        self.push_stack = []

    # Make a copy of the stack when copying the state.
    def copy(self):
        rv = paren_state()
        rv.push_stack = list(self.push_stack)
        return rv

    # The transition() method does most of the step visitor work.
    def transition(self,
                   srcpt,
                   edgelabel,
                   destpt,
                   tosrc_xform,
                   edge_xform,
                   tosrc_path):
        
        # First, check whether the source point at this CFG edge is a
        # call-site to one of the functions we are interested in.
        src_calls_open  = [fname for fname in ['openParen', 'openBracket']
                           if point_calls_function(srcpt, fname)]
        src_calls_close  = [fname for fname in ['closeParen', 'closeBracket']
                            if point_calls_function(srcpt, fname)]
        dest_calls_close  = [fname for fname in ['closeParen', 'closeBracket']
                             if point_calls_function(destpt, fname)]
     
        print 'Testing 1, 2, 3... This will show up in the analysis log page.'

        # If the source point is a call-site to openParen() or
        # openBracket(), update the state by pushing the appropriate
        # kind of parenthesis onto the stack.
        if src_calls_open:
            self.push_stack.append('(' if 'openParen' in src_calls_open else '[')

        # If the source point is a call site to closeParen() or
        # closeBracket(), update the state by popping the stack. No
        # checking needs to be carried out here, as it was already
        # carried out when traversing into srcpt (see below)
        elif src_calls_close:
            if len(self.push_stack)>0:
                self.push_stack.pop()
 
        # If the destination point is a call site to closeParen() or
        # closeBracket(), check to make sure the corresponding '(' or
        # ']' is on top of the stack and issue an appropriate warning
        # if not.
        if dest_calls_close:
            if self.push_stack:
                stacktop = self.push_stack[-1]

                # closeParen without matching '(' on top of the stack
                # -> issue a 'mismatched' warning.
                if 'closeParen' in dest_calls_close and stacktop != '(':
                    mismatched_wc.report(tosrc_path)

                # closeBracket without matching '[' on top of the stack
                # -> issue a 'mismatched' warning.
                elif 'closeBracket' in dest_calls_close and stacktop != '[': 
                   mismatched_wc.report(tosrc_path)

            # closeParen or closeBracket with empty stack (no top at all)
            # -> issue a 'missing open' warning
            else:
                missing_open_wc.report(tosrc_path)
            
        # Traversal is about to exit the function while there
        # are outstanding unbalanced opening parentheses
        # -> issue a 'missing close' warning 
        if (destpt.get_kind() == cs.point_kind.EXIT) and self.push_stack:
            missing_close_wc.report(tosrc_path)

# We defined paren_state.__init__ to suitably initialize the state, so
# just pass a new instance to cs.analysis.add_step_bottom_up_visitor()

cs.analysis.add_step_bottom_up_visitor(paren_state())
