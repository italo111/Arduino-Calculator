#include<Keypad.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd (A0, A1, A2, A3, A4, A5);
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};
int sum =0;
int temp = 0,temp1 = 0,temp2 = 0;
int count = 0;
String str = "";
int i = 0;
int i2 = 0;
bool stop = false;

Keypad customKeypad = Keypad(makeKeymap(hexaKeys),rowPins, colPins, ROWS,COLS);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  //lcd.setCursor(0,0);
  //lcd.print("Calculator: ");
  if(!stop){
    lcd.setCursor(0,0);
  lcd.print("Calculator: ");
  }
char customKey = customKeypad.getKey();
delay(20);
//----------
if(customKey == 'C'){
  lcd.setCursor(0,0);
  lcd.print("Exiting...");
  stop = true;
}
if(customKey == 'D'){//restarts
  lcd.setCursor(0,0);
  lcd.print("Calculator:");
  stop = false;
  customKey = '0';
  i--;
}
//------------
if(customKey && !stop ){
  count++;
  //process the calculation
  if(count == 1){
    temp = (int)customKey-48;
    bool flag = false;
     str = str + String (temp);
     
    while(!flag){
      customKey = customKeypad.getKey();
      delay(20);
      if(customKey){
            if(isDigit(customKey)){
              str = str + String(customKey);
              i++;
              
            }
            else{
                count++;//will skip count == 2
                temp = str.toInt();
                flag = true;
                temp1 = customKey;
                i++;
                if(temp1 == 'A'){
                 
                  lcd.setCursor(0,1);
                  lcd.print(temp);
                  lcd.print('+');
                  
                }else if(temp1 == 'B'){
                  lcd.setCursor(0,1);
                  lcd.print(temp);
                  lcd.print('-');
                  
                }
                
            }
    }
  }
    
} 
  else if(count == 3){
    temp2 = (int)customKey-48;
    //---------------------
       bool flag = false;
       str = "";
     str = str + String (temp2);
     i2++;
     i++;
    while(!flag){
      customKey = customKeypad.getKey();
      if(customKey){
            if(isDigit(customKey)){
              str = str + String(customKey);
              
              i2++;
            }
            else if(customKey == '*'){
                temp2 = str.toInt();
                flag = true;
                lcd.setCursor(i,1);
                lcd.print(temp2);
                lcd.setCursor(i+i2,1);
                lcd.print('=');
                i++; //counting the = character
                
  
            }
    }
  }
    

   //-----------------------
    if(temp1 == 'A'){
          sum = temp + temp2;
    }
    else if(temp1 == 'B'){
      sum = temp - temp2;
    }
     Serial.println(sum);
     i++;
     i2--;
     lcd.setCursor(i+i2,1);
     lcd.print(sum);
     delay(6000);
     lcd.clear();
     
     
    //reset all values again
    sum = 0;
    temp = 0;
    temp1 = 0;
    temp2 = 0;
    count = 0;
    str ="";
    i =0;
    i2=0;
    
  }
  
}


}
