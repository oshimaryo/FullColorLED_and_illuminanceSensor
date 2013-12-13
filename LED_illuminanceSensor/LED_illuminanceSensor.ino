int r = 9, b = 10, g = 11;
int sensor_pin = A0;

int count = 0; 
int state = 0; // 0:RED 1:BLUE 2:GREEN
boolean change = false;

int threshold =990;
int sensor_value = 0;

void setup() {
  Serial.begin(9600);

  analogWrite(r,0);
  analogWrite(b,0);
  analogWrite(g,0);
}


void loop() {

  // R
  if(state%3 == 0){
    if(count%512 > 255) analogWrite(r, culc(count%256));
    else analogWrite(r, culc(256-(count%256)) );
    analogWrite(b,0);
    analogWrite(g,0);
  }
  // B
  else if(state%3 == 1){
    if(count%512 > 255) analogWrite(b, culc(count%256));
    else analogWrite(b, culc(255-(count%256)) );
    analogWrite(r,0);
    analogWrite(g,0);
  }
  // G
  else if(state%3 == 2){
    if(count%512 > 255) analogWrite(g, culc(count%256));
    else analogWrite(g, culc(255-(count%256)) );
    analogWrite(b,0);
    analogWrite(r,0);
  }


  // use Illuminance Sensor as a Touch Sensor
  sensor_value = analogRead(sensor_pin);  // get illuminance Sensor
  //  Serial.println(sensor_value);

  if(sensor_value > threshold && change == false){
    state++;
    change = true;
  }
  else if(sensor_value <= threshold){
    change = false;
  } 

  count++;

  delay(5);
}

// culculation for LED Modulation
int culc(int val){
  return (double)val* (double)val/255.0 +0;
}

