# upload and analyze a codebase using CodeDX REST API
# invocation:
# python AnalyzeCodebase.py "GROUP NAME" "CODE BASE" username password 
# eg:
#	python AnalyseCodebase.py "REST API"  .\demosource.zip admin admin
# "GROUP NAME" should already exist in your CodeDX repository
# general Codedx assigned password is C0d3DX1 (I changed from Vinces preference to mine, "admin")
#
# needed to add "requests" module to my python (C:\Python36-32/python.exe):
#	pip install requests
# useful website - convert curl cmd line requests into python
#	https://curl.trillworks.com/

import sys
import requests # for curl/http[s] requests
import json

if len(sys.argv) != 5:
	print ("\n*** ERROR: must be 4  args passed to script - see top of " + sys.argv[0] + " for details.")
	sys.exit()

# step 1 - check "GROUP NAME" exists using python curl support
url='http://127.0.0.1/codedx/api/projects/query'
headers = {
    'accept': 'application/json',
    'Content-Type': 'application/json',
}

data = '{ "filter": { "name": "'+sys.argv[1]+'" }}'
# verify=False avoids SSL certificate checking....
response = requests.post(url, headers=headers, data=data, auth=(sys.argv[3], sys.argv[4]), verify=False)
text = response.json()

if (len(text) == 0):
	print ("\n*** ERROR: " + sys.argv[1] + " not found")
	sys.exit()


# get the projectID for requested project name
projectId = text[0]['id']

# step 2 - Create Analysis Prep
headers = {
    'accept': 'application/json',
    'Content-Type': 'application/json',
}
data = '{ "projectId": '+str(projectId)+'}'
response = requests.post('http://127.0.0.1/codedx/api/analysis-prep', headers=headers, data=data, auth=(sys.argv[3], sys.argv[4]), verify=False)
text = response.json()

# ************ to do: some error handling for bad responses

# get the prepID for requested analysis prep
prepID = text['prepId']

# step 3 - upload file to analysis prep

files = {
     'file':('Demo Source', open(sys.argv[2],'rb'),'application/x-zip-compressed'),
}

response = requests.post('http://127.0.0.1/codedx/api/analysis-prep/'+prepID+'/upload', files=files, auth=(sys.argv[3], sys.argv[4]), verify=False)
text = response.json()
print (text)
# step 4 - Run Prepared Analysis

headers = {
    'accept': 'application/json',
}

response = requests.post('http://127.0.0.1/codedx/api/analysis-prep/'+prepID+'/analyze', headers=headers, auth=(sys.argv[3], sys.argv[4]), verify=False)
text = response.json()
print (text)