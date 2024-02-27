
try:
    with open("sast-summary-report.md", "r") as data:
        data.read()
except IOError:
    print("Problem reading the report")
