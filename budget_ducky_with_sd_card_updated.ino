// Net_Code
// 7-28-2022
#include <SPI.h>
#include <SD.h>
#include <string.h>
#include "Keyboard.h"
// #include "usb_hid_codes.h"

// I think I need to add 136 to every one of the values but I can check that with a HID scan code table

File myFile;
boolean first = true;
// the file that will be run when powered on
String DEFAULT_FILE_NAME = "file.txt";
String LAST_STRING_RUN = "this failed";
String LAST_STRING_RUN0 = "this failed";
String LAST_STRING_RUN1 = "this failed";
String LAST_STRING_RUN2 = "this failed";
String LAST_STRING_RUN3 = "this failed";
String LAST_STRING_RUN4 = "this failed";
String LAST_STRING_RUN5 = "this failed";
String LAST_STRING_RUN6 = "this failed";
String LAST_STRING_RUN7 = "this failed";
String LAST_STRING_RUN8 = "this failed";

void setup() {
  // if there is no SD card, quit
  if (!SD.begin(4)) {
    return;
  }
  // open the default file
  myFile = SD.open(DEFAULT_FILE_NAME);
  if (myFile) {
    Keyboard.begin();
    // start reading the lines of the file
    String line = "";
    while (myFile.available()) {
      // read in the line from the default file
      char m = myFile.read();
      // this does some funky stuff, but putting my copy line here seems to work as intended
      if (m == '\n'){
        Line(line);
        LAST_STRING_RUN8 = LAST_STRING_RUN7;
        LAST_STRING_RUN7 = LAST_STRING_RUN6;
        LAST_STRING_RUN6 = LAST_STRING_RUN5;
        LAST_STRING_RUN5 = LAST_STRING_RUN4;
        LAST_STRING_RUN4 = LAST_STRING_RUN3;
        LAST_STRING_RUN3 = LAST_STRING_RUN2;
        LAST_STRING_RUN2 = LAST_STRING_RUN1;
        LAST_STRING_RUN1 = LAST_STRING_RUN0;
        LAST_STRING_RUN0 = LAST_STRING_RUN;
        LAST_STRING_RUN = line;
        line = "";
        }
        // don't fully understand this but it makes it work so don't touch it and don't question it
        else if((int) m != 13)
        {
          line += m;
        }
    }
    // This is some trickery to keep a copy of the last command that was run,
    // and then overwrite it the next time a command is run, but critically
    // the command is saved after the command is run, so if the command
    // is "REPEAT" it can grab the copy of the command that was run right
    // before, and then once the REPEAT command is done running the backup of
    // the last command will be overwritten by the command that was just run,
    // so in this example it would be overwritten by the command "REPEAT x"
    // (where x is the number of times to repeat).
    // Line("STRING " + LAST_STRING_RUN );
    // LAST_STRING_RUN = line;
    Line(line);

    myFile.close();
  } else { /* take a wild guess */ }

  Keyboard.end();
}
void Line(String STRING_ONE)
{
  // find the first space and save the location of it, if there isn't a space,
  // than just take the string and send it the Press function. If there is a
  // space in the string then continue checking to see if it's one of the
  // commands that takes arguments.
  int space_1 = STRING_ONE.indexOf(" ");
  if (space_1 == -1)
  {
    Press(STRING_ONE);
  }
  // PRINT just prints the rest of the text on the line by using substring to grab everything after the first space
  else if (STRING_ONE.substring(0,space_1) == "STRING")
  {
    Keyboard.print(STRING_ONE.substring(space_1 + 1));
  }
  // DELAY by however many milliseconds by just using the built in delay function that is part of the Arduino codebase
  else if (STRING_ONE.substring(0,space_1) == "DELAY")
  {
    int delaytime = STRING_ONE.substring(space_1 + 1).toInt();
    delay(delaytime);
  }
  // REM is just comments, so you can comment out sections of the script, I
  // recommend using batch file syntax highlighting when writing duckyscript
  else if(STRING_ONE.substring(0,space_1) == "REM"){ /* as you can see, it does nothing and ignores the rest of the line*/}

    // the repeat function so I don't have to write out "down \n delay 200" ten thousand times in a row
    // FUCK YOU DELL, FUCK YOUR TERRIBLE BIOS/UEFI KEYBOARD NAVIGATION
  else if (STRING_ONE.substring(0,space_1) == "REPEAT")
  {
    bool DONE_YET = false;
    int counter = 0;
    int numberOfTimesToRepeat = STRING_ONE.substring(space_1 + 1).toInt();
    // run through the while loop until counter is greater than or equal to the number of times it's supposed to repeat
    while(!DONE_YET) {
      if(counter >= numberOfTimesToRepeat) {
        DONE_YET = true;
      }
      else{
        delay(200);
        // Line("STRING " + LAST_STRING_RUN + "\n");
        Line(LAST_STRING_RUN);
        counter++;
      }
    }
    DONE_YET = false;

  }

  else if (STRING_ONE.substring(0,space_1) == "LOOP")
  {
    int counter = 0;
    int latest_space = STRING_ONE.indexOf(" ", space_1 + 1);
    int numberOfLinesToLoop = STRING_ONE.substring(space_1 + 1, latest_space).toInt();
    int numberOfTimesToLoop = STRING_ONE.substring(latest_space + 1).toInt();
    // run through the while loop until counter is greater than or equal to the number of times it's supposed to repeat
    bool DONE_YET0 = false;
    while(!DONE_YET0) {
      if(counter >= numberOfTimesToLoop) {
        DONE_YET0 = true;
      }
      else{
        // I want to pull the number of lines to loop, and then in addition pull the number of times to loop those lines, for instance LOOP 3 2 to run the last 4 lines 16 times
        // Once I have those numbers I can throw them in this else block and pull the saved lines up to the number of lines that were called for, in the last example 3, and then run them in order 2 times
        if (numberOfLinesToLoop <= 1){
          Line(LAST_STRING_RUN);
        }
        else if (numberOfLinesToLoop <= 2){
          Line(LAST_STRING_RUN);
          Line(LAST_STRING_RUN0);
        }
        else if (numberOfLinesToLoop <= 3){
          Line(LAST_STRING_RUN);
          Line(LAST_STRING_RUN0);
          Line(LAST_STRING_RUN1);
        }
        else if (numberOfLinesToLoop <= 4){
          Line(LAST_STRING_RUN);
          Line(LAST_STRING_RUN0);
          Line(LAST_STRING_RUN1);
          Line(LAST_STRING_RUN2);
        }
        else if (numberOfLinesToLoop <= 5){
          Line(LAST_STRING_RUN);
          Line(LAST_STRING_RUN0);
          Line(LAST_STRING_RUN1);
          Line(LAST_STRING_RUN2);
          Line(LAST_STRING_RUN3);
        }
        else if (numberOfLinesToLoop <= 6){
          Line(LAST_STRING_RUN);
          Line(LAST_STRING_RUN0);
          Line(LAST_STRING_RUN1);
          Line(LAST_STRING_RUN2);
          Line(LAST_STRING_RUN3);
          Line(LAST_STRING_RUN4);
        }
        else if (numberOfLinesToLoop <= 7){
          Line(LAST_STRING_RUN);
          Line(LAST_STRING_RUN0);
          Line(LAST_STRING_RUN1);
          Line(LAST_STRING_RUN2);
          Line(LAST_STRING_RUN3);
          Line(LAST_STRING_RUN4);
          Line(LAST_STRING_RUN5);
        }
        else if (numberOfLinesToLoop <= 8){
          Line(LAST_STRING_RUN);
          Line(LAST_STRING_RUN0);
          Line(LAST_STRING_RUN1);
          Line(LAST_STRING_RUN2);
          Line(LAST_STRING_RUN3);
          Line(LAST_STRING_RUN4);
          Line(LAST_STRING_RUN5);
          Line(LAST_STRING_RUN6);
        }
        else if (numberOfLinesToLoop <= 8){
          Line(LAST_STRING_RUN);
          Line(LAST_STRING_RUN0);
          Line(LAST_STRING_RUN1);
          Line(LAST_STRING_RUN2);
          Line(LAST_STRING_RUN3);
          Line(LAST_STRING_RUN4);
          Line(LAST_STRING_RUN5);
          Line(LAST_STRING_RUN6);
          Line(LAST_STRING_RUN7);
        }
        else if (numberOfLinesToLoop <= 8){
          Line(LAST_STRING_RUN);
          Line(LAST_STRING_RUN0);
          Line(LAST_STRING_RUN1);
          Line(LAST_STRING_RUN2);
          Line(LAST_STRING_RUN3);
          Line(LAST_STRING_RUN4);
          Line(LAST_STRING_RUN5);
          Line(LAST_STRING_RUN6);
          Line(LAST_STRING_RUN7);
          Line(LAST_STRING_RUN8);
        }



        counter++;
      }
    }
    DONE_YET0 = false;
  }

  else
  {
      String remain = STRING_ONE;

      while(remain.length() > 0)
      {
        int latest_space = remain.indexOf(" ");
        if (latest_space == -1)
        {
          Press(remain);
          remain = "";
        }
        else
        {
          Press(remain.substring(0, latest_space));
          remain = remain.substring(latest_space + 1);
        }
        delay(5);
      }
  }

  Keyboard.releaseAll();
}


void Press(String b)
{
  // checks to see if the string is more than one char long, and if its only
  // one it just sends that key, but if its longer it assumes its a control
  // char and tests to see if its one of the ones below, if it's not it does
  // nothing and moves on
  if(b.length() == 1)
  {
    char c = b[0];
    Keyboard.press(c);
  }
  else if (b.equals("ENTER"))
  {
    Keyboard.press(KEY_RETURN);
  }
  else if (b.equals("CTRL"))
  {
    Keyboard.press(KEY_LEFT_CTRL);
  }
    else if (b.equals("SHIFT"))
  {
    Keyboard.press(KEY_LEFT_SHIFT);
  }
    else if (b.equals("ALT"))
  {
    Keyboard.press(KEY_LEFT_ALT);
  }
    else if (b.equals("GUI"))
  {
    Keyboard.press(KEY_LEFT_GUI);
  }
    else if (b.equals("UP") || b.equals("UPARROW"))
  {
    Keyboard.press(KEY_UP_ARROW);
  }
    else if (b.equals("DOWN") || b.equals("DOWNARROW"))
  {
    Keyboard.press(KEY_DOWN_ARROW);
  }
    else if (b.equals("LEFT") || b.equals("LEFTARROW"))
  {
    Keyboard.press(KEY_LEFT_ARROW);
  }
    else if (b.equals("RIGHT") || b.equals("RIGHTARROW"))
  {
    Keyboard.press(KEY_RIGHT_ARROW);
  }
    else if (b.equals("DELETE"))
  {
    Keyboard.press(KEY_DELETE);
  }
    else if (b.equals("PAGEUP"))
  {
    Keyboard.press(KEY_PAGE_UP);
  }
    else if (b.equals("PAGEDOWN"))
  {
    Keyboard.press(KEY_PAGE_DOWN);
  }
    else if (b.equals("HOME"))
  {
    Keyboard.press(KEY_HOME);
  }
    else if (b.equals("ESC"))
  {
    Keyboard.press(KEY_ESC);
  }
    else if (b.equals("INSERT"))
  {
    Keyboard.press(KEY_INSERT);
  }
    else if (b.equals("TAB"))
  {
    Keyboard.press(KEY_TAB);
  }
    else if (b.equals("END"))
  {
    Keyboard.press(KEY_END);
  }
    else if (b.equals("CAPSLOCK"))
  {
    Keyboard.press(KEY_CAPS_LOCK);
  }
    else if (b.equals("F1"))
  {
    Keyboard.press(KEY_F1);
  }
    else if (b.equals("F2"))
  {
    Keyboard.press(KEY_F2);
  }
    else if (b.equals("F3"))
  {
    Keyboard.press(KEY_F3);
  }
    else if (b.equals("F4"))
  {
    Keyboard.press(KEY_F4);
  }
    else if (b.equals("F5"))
  {
    Keyboard.press(KEY_F5);
  }
    else if (b.equals("F6"))
  {
    Keyboard.press(KEY_F6);
  }
    else if (b.equals("F7"))
  {
    Keyboard.press(KEY_F7);
  }
    else if (b.equals("F8"))
  {
    Keyboard.press(KEY_F8);
  }
    else if (b.equals("F9"))
  {
    Keyboard.press(KEY_F9);
  }
    else if (b.equals("F10"))
  {
    Keyboard.press(KEY_F10);
  }
    else if (b.equals("F11"))
  {
    Keyboard.press(KEY_F11);
  }
    else if (b.equals("F12"))
  {
    Keyboard.press(KEY_F12);
  }
    else if (b.equals("SPACE"))
  {
    Keyboard.press(' ');
  } 
}

void loop() {
  // nothing happens after setup
}
