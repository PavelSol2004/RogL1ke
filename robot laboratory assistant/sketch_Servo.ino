#include <Servo.h>

class Articul;

Articul** Artic_array;  // (**(Artic_array + using_id))

static int id = 0;
class Articul
{
  Servo Join;
  int pin;
  int Join_id;

public:
  Articul(int pin)
  {
    this->pin = pin;
    id++;
    this->Join_id = id;

    Articul** New_Art_arr = new Articul * [id];

		for (int i = 0; i < id-1; i++)
		{
			*(New_Art_arr + i) = *(Artic_array + i);
		}

		*(New_Art_arr + id - 1) = this;

		if (id != 1)
		{
			delete[] Artic_array;
		}

		Artic_array = New_Art_arr;
  }

  void SetAngle(int angle)
  {
    while(Join.read()!=angle)
    {
      Join.write(angle);
      delay(500);
    }
    
    
  }

  int Get_Pin()
  {
    return this->pin;
  }

  void Attach()
  {
    this->Join.attach(this->pin);
  }
  
};

void Attach_All()
{
  for(int using_id = 0; using_id<id; using_id++)
  {
    (**(Artic_array + using_id)).Attach();
  }
}

 Articul X_Artic(9);

void setup() {
  Serial.begin(9600);
  
  Attach_All();
  
}

void loop() {
  
  if(Serial.available())
  {
    
    int exp = Serial.parseInt();

    if(exp)
    {
      X_Artic.SetAngle(exp);
    }
  }
  
}

/*
switch (exp)
	  {
    case 2: X_Artic.SetAngle(45);
      
      Serial.println(" 2");
      break;     
    case 1: X_Artic.SetAngle(180);
      
      Serial.println(" 1");
      break;
	  default: Serial.println("Nothing");
		  break;
	  }    

*/