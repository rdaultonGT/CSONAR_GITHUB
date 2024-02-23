import java.beans.Statement;
import java.io.BufferedReader;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
import javax.servlet.*;
import javax.servlet.http.*;

import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathConstants;
import javax.xml.xpath.XPathExpressionException;

import org.w3c.dom.Document;

public class MyServletDemo extends HttpServlet {

   private String mymsg;
   private GenericServlet logger = null;

   public void init() throws ServletException {
      mymsg = "Hello World!aaaaaqqqqqq";
   }

   public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException { 
	  String param1 = request.getParameter("param1");
	  response.setContentType("text/html");
      
      String op = request.getParameter("name"), param = request.getParameter("param"), COOKIENAME = "test_cookie", data = "00000000000";
      
      Cookie c = new Cookie(COOKIENAME, data);
      c.setHttpOnly(false);  
            
      if (op.equals("cmdi"))    	  
    	 cmd_i (request, response);
      else if (op.equals("xpath")){
    	boolean j = false;
		XPath xpath = null;
		try {
			
			Document doc = null;
			j = authenticatexpath (request, (javax.xml.xpath.XPath ) xpath,  (org.w3c.dom.Document) doc);
			System.out.println(j);
			
			logger.log(".." + j);
			
		} catch (XPathExpressionException e) {
			e.printStackTrace();
		}
      }
      else if (op.equals("xss")){
    	  xss (request, response);  
      }
      else if (op.equals("serial")){
    	  try {
			serial (request, response);
		} catch (ClassNotFoundException | IOException e) {
			e.printStackTrace();
		}
      }
      else if (op.equals("connect"))
      {
    	  connectdb(request,response);
      }
      else if (op.equals("sqli")){
    	  Connection n = null;
    	  String user = null;
    	  String user_par = request.getParameter("user");
    	  
    	  try {
			sqli(request,response, n, user, user_par);
		} catch (SQLException e) {
			e.printStackTrace();
		}
      }
      else if (op.equals("dos")) {
    	  dos();
      }
   }
	

public void cmd_i(HttpServletRequest request, HttpServletResponse response) throws IOException {
	   
	   Runtime rt = Runtime.getRuntime();
	   System.out.println ("Executing commands");
	   Process proc = rt.exec(request.getParameter("param"));
       
       BufferedReader stdInput = new BufferedReader(new InputStreamReader(proc.getInputStream()));
       
       System.out.println("Here is the standard output of the command:\n");
       
       String s = null;
       while ((s = stdInput.readLine()) != null) {
    	   PrintWriter out = response.getWriter();
    	   out.write(s + '\n'); 
       }
       
       
       Runtime.getRuntime().exec("make"); 
       Runtime.getRuntime().exec(new String[]{"make"});  

       ProcessBuilder builder = new ProcessBuilder("make");  
       builder.command("make");  
   
   }
   
   public void dynamicce (HttpServletRequest request, HttpServletResponse response) throws ScriptException {
	   String input = request.getParameter("input");

	   ScriptEngineManager manager = new ScriptEngineManager();
	   ScriptEngine engine = manager.getEngineByName("JavaScript");
	   engine.eval(input); 
   }
   
   
   public void xss (HttpServletRequest request, HttpServletResponse response) throws IOException {
	   
	   String name = request.getParameter("param");
	   PrintWriter out = response.getWriter();
	
	   response.setHeader("Set-Cookie", "AAAAAAAAAAAAAAAAAAAA");  
	   Cookie cookie = new Cookie("jsessionid", "AAAAAAAAAAAAAAAAAAAA");  
	   response.addCookie(cookie);
	   
	   out.write("Hello " + name); 	   
   }
   
   public void ssrf (HttpServletRequest request, HttpServletResponse response) throws IOException {
	   InetAddress inet;
	   PrintWriter out = response.getWriter();
	   inet = InetAddress.getByAddress(new byte[] { 127, 0, 0, 1 });
	   System.out.println("Sending Ping Request to " + inet);
	   out.write(" " + inet.isReachable(5000));
 
   }
   public void connectdb (HttpServletRequest request, HttpServletResponse response) {
	   
	   
   }
   public void serial (HttpServletRequest request, HttpServletResponse response) throws IOException, ClassNotFoundException {
	   //ReqProc x = new ReqProc();
	   //x.processRequest(request);
    
   }
   
   public void dos () {
	   java.util.regex.Pattern.compile("(h|h|ih(((i|a|c|c|a|i|i|j|b|a|i|b|a|a|j))+h)ahbfhba|c|i)*").matcher(
			   "hchcchicihcchciiicichhcichcihcchiihichiciiiihhcchi"+
			   "cchhcihchcihiihciichhccciccichcichiihcchcihhicchcciicchcccihiiihhihihihi"+
			   "chicihhcciccchihhhcchichchciihiicihciihcccciciccicciiiiiiiiicihhhiiiihchccch"+
			   "chhhhiiihchihcccchhhiiiiiiiicicichicihcciciihichhhhchihciiihhiccccccciciihh"+
			   "ichiccchhicchicihihccichicciihcichccihhiciccccccccichhhhihihhcchchihih"+
			   "iihhihihihicichihiiiihhhhihhhchhichiicihhiiiiihchccccchichci").matches(); 
   }
   
   public void sqli(HttpServletRequest request, HttpServletResponse response, Connection con, String user, String user2) throws SQLException {
	   
		   Statement stmt1 = null;
		   Statement stmt2 = null;
		   PreparedStatement pstmt;
	
		     stmt1 = (Statement) con.createStatement();
		     ResultSet rs1 = ((java.sql.Statement) stmt1).executeQuery("GETDATE()"); 

		     stmt2 = (Statement) con.createStatement();
		     ResultSet rs2 = ((java.sql.Statement) stmt2).executeQuery("select FNAME, LNAME, SSN " + "from USERS where UNAME=" + user);  

		     pstmt = con.prepareStatement("select FNAME, LNAME, SSN " + "from USERS where UNAME=" + user2);  
		     ResultSet rs3 = pstmt.executeQuery();
		   

   }
   
   public boolean authenticatexpath(javax.servlet.http.HttpServletRequest request, javax.xml.xpath.XPath xpath, org.w3c.dom.Document doc) throws XPathExpressionException {
	   String user = request.getParameter("user");
	   String pass = request.getParameter("pass");

	   String expression = "/users/user[@name='" + user + "' and @pass='" + pass + "']"; 
	   return (boolean)xpath.evaluate(expression, doc, XPathConstants.BOOLEAN); 
	 }
   
   public void destroy() {
      /* leaving empty for now this can be
       * used when we want to do something at the end
       * of Servlet life cycle
       */
   }
}