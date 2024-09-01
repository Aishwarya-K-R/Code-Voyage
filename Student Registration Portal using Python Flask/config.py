
import os

class Config(object):
    SECRET_KEY = os.environ.get('SECRET_KEY') or b'6\xe9\xda\xead\x81\xf7\x8d\xbbH\x87\xe8m\xdd3%' # special key used in python and flask as a signature key which ensures that anything we set across the server is not open to hackers for hacking
    # Cookies use the same principle

    MONGODB_SETTINGS = { 'db' : 'UTA_Enrollment' } # setting up the mongodb database
