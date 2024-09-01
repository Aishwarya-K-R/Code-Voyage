# This file takes care of all the initialization

from flask import Flask # Flask class
from config import Config
from flask_mongoengine import MongoEngine # type: ignore

app = Flask(__name__) # initialising the name of our application from the rendered app name in .flaskenv file
app.config.from_object(Config) # loading the congigurations from config.py file

db = MongoEngine() # instantiating the MongoEngine() class
db.init_app(app) # initializing the app

from application import routes


