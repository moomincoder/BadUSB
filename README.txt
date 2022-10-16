Moomincoder
7-28-2022

The BadUSB device I made reads Duckyscript and you can find good tutorials for it online, or just
create new scripts based on the ones that are already on it.
It will only attempt to run the file named "file.txt" so anything else there is ignored (like this one)


EXTRA NOTES
I haven't added the DEFAULT_DELAY option, the total list of commands is below

If you want to print text use "STRING"
Comments are REM.
And you can use just single char from the keyboard by, for example, using "a", and it will just 
press the letter "a".  It doesn't support "A", to get that use "SHITFT a".
If you want to use multiple at a time, like above, to open run in Windows use "GUI r", and then 
print whatever you want.

I've never even tried to use CAPSLOCK so I'm not sure if CAPSLOCK is a toggle or not, I wouldn't
bother trying to find out, it doesn't really matter that much, just use "SHIFT (the string you 
want)" and I'm pretty sure that would work.

I recommend using batch file syntax highlighting when writing duckyscript

"ENTER"
"CTRL"
"SHIFT"
"ALT"
"GUI"
"UP" || "UPARROW"
"DOWN" || "DOWNARROW"
"LEFT" || "LEFTARROW"
"RIGHT" || "RIGHTARROW"
"DELETE"
"PAGEUP"
"PAGEDOWN"
"HOME"
"ESC"
"INSERT"
"TAB"
"END"
"CAPSLOCK"
"F1"
"F2"
"F3"
"F4"
"F5"
"F6"
"F7"
"F8"
"F9"
"F10"
"F11"
"F12"
"SPACE"
"DELAY" "a single space" "the number of milliseconds you want it to wait"
"REM" it will ignore everything after this on that line, if you want a mutiline
comment you will need to add another REM statement and then continue on that line
"STRING" "a single space" "the string that you want to have written"
"REPEAT" "a single space" "the number of times you want the last command run"
"LOOP" "a single space" "the number of lines you want to run" "a single space" "the number of times you want to run those lines"

REPEAT is a bit weird, but it is run after the command that you want to repeat, so the command will be run once, and then repeat will run it however many extra times you want it run.
For instance,
DOWN
REPEAT 3
This will run the command "DOWN" 4 times in a row, with a 200mill delay between each press.
There is a hardcoded 200mill delay between each repeated command, for instance, "DOWN" would be run like "DOWN" wait 200mill "DOWN" and continue like that.
The 200mill delay is run before the command is run, so for example this
DOWN
REPEAT 3

would run what is essentially this
DOWN
(DELAY 200)
DOWN
(DELAY 200)
DOWN
(DELAY 200)
DOWN
The thing you need to be careful with here is there is not delay after the last copy of the command is run, so you will need to manualy run DELAY 200 before the next command that is run after the REPEAT command.
BE EXTREMELY CAREFUL NOT TO HAVE TWO REPEATS IN A ROW AS THAT WILL LEAD TO A CLUSTERFUCK YOU DON'T WANT TO DEAL WITH.

LOOP works the same way as REPEAT, but it doesn't have a built in delay, AND YOU SHOULD NEVER INCLUDE A REPEAT INSIDE A BLOCK THAT IS BEING LOOPED, IT DOES NOT END WELL.
