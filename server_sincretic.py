from flask import Flask
import serial
app = Flask(__name__)

ser = serial.Serial('COM5')
print(ser.name) 

@app.route('/')
def hello_world():
    
    #temp = '- Temperatura este '
    encoding = 'utf-8'
   
    temp_serial = ser.readline()
    
    stringul_extra = """


<!DOCTYPE html>
<html>
<head>
<style>
.button {
  background-color: #4CAF50; /* Green */
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button4 {background-color: #e7e7e7; color: black;} /* Gray */
.button2 {background-color: #008CBA;} /* Blue */
body {
  background-image: url('https://images.wallpaperscraft.com/image/sunset_sky_gradient_202976_1600x1200.jpg');
}
</style>
</head>
<body>

<h2>Proiect Sincretic 2021 </h2>
<p></p>


<button class="button button4" onclick="document.location=\'led_off\'">LED OFF</button>
<button class="button" onclick="document.location=\'led_on\'">LED ON</button>
"""+ ' <p> <h3>Temperatura este: </h3> <button class="button button2">' + temp_serial.decode(encoding) + """</button> </p>
</body>
</html>

"""




    
    return stringul_extra
    
@app.route('/led_on')
def led_on():
    ser.write("A".encode())
    string_buton = '<p><a href="http://127.0.0.1:5000/">Back</a></p>'

    return "Am aprins ledul" + string_buton + ""

@app.route('/led_off')
def led_off():
    ser.write("S".encode())
    string_buton = '<p><a href="http://127.0.0.1:5000/">Back</a></p>'
    return "Am stins ledul" + string_buton
