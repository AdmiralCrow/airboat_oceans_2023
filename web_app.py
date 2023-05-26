from pymongo import MongoClient
import cesarBoat
from datetime import datetime

tempF=cesarBoat.read_temp()
# create a MongoClient object to connect to your MongoDB instance
#client = MongoClient('localhost', 27017)  # replace 'localhost' with the IP address of your MongoDB instance if it's not on your Raspberry Pi
client = MongoClient("mongodb+srv://test_user:test_user@learningmongodb.ra1bm.mongodb.net/db?retryWrites=true&w=majority")


print(client.test)# specify the database and collection
db = client.db
collection = db.my_collection

# example data from a sensor
sensor_data = {
    'temperature': tempF, 
    'humidity': 45.2, 
    'timestamp': datetime.now()
}

print(db)
print(collection)

collection.insert_one(sensor_data)

documents = collection.find()

for doc in documents:
    print(doc)