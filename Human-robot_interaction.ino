#include<Wire.h>
#include<Zumo32U4.h>


// instanciate the different Zumo classes
Zumo32U4Buzzer buzzer;
Zumo32U4Motors motors;
Zumo32U4LCD lcd;
Zumo32U4Encoders encoders;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;

int accCountsR = 0;
int commandsSelected = 0; // 0 -> F, 1 -> backwards, 2 -> right, 3 -> left

int actualStage = 0;


void setup() {
  Serial.begin(9600);
  lcd.clear();
  
}



void loop() {
      // Stage -> Select command
        if (actualStage == 0) {
        stage0();
        delay(200);
        }

    // stage 1 --> Select speed and time
        if (actualStage == 1) {
          stage1();
          delay(200);
        }

    // stage 2 --> Run the program


  
}

void stage0() {
      // Stage 0 --> select command
        
         // read the encoders (function)
        readEncoderStage0();
        
         // if it's larger or lower than threshold then
            // increment or decrement the selected command
       if (accCountsR > 100) {
          beep();
          commandsSelected += 1;
          accCountsR -= 100;
          if (commandsSelected > 3) commandsSelected = 0;
       } else if (accCountsR < -100) {
        beep();
        commandsSelected -= 1;
        accCountsR += 100;
          if (commandsSelected < 0) commandsSelected = 3;
       }

       Serial.println("Counts: " + String(accCountsR) + "\n" + "Command: " + String(commandsSelected));
          
        //Show it on the screen
            //Title
            //In which command we are 
        LCD_stage0(commandsSelected);

        
        //Until button pressed?
            //if yes I jump to the next stage and store the command
        if (buttonA.isPressed()) {
          actualStage = 1;
          buttonA.waitForPress();
        }
}

void LCD_stage0(int command) {
  String nameCommand;
  switch (command) {
    case 0:
    nameCommand = "Forward";
    break;
    
    case 1:
    nameCommand = "Backward";
    break;
    
    case 2:
    nameCommand = "Right";
    break;
 
    case 3:
    nameCommand = "Left";
    break;

    default:
    nameCommand = "Error";
  }
  
  lcd.clear();
  lcd.print("Command>");
  lcd.gotoXY(0,1);
  lcd.print(nameCommand);
}

void beep() {
  buzzer.playNote(NOTE_A(4), 20, 15);
}

void stage1() {
          // read the encoders (same function)
       lcd.clear();
       lcd.print((String)commandsSelected);
        // if it's larger or lower than threshold then
            // increment or decrement the selected command  

        //Show the Speed on the screen
}

void readEncoderStage0() {
  accCountsR += encoders.getCountsAndResetRight(); //accCountsR = accCountsR + encoders.getCountsAndResetRight();
}
