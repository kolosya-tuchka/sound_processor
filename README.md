# sound_processor
 The program launches using terminal 
 Command example: 
 ./sound_processor "input1.wav" "input2.wav" "input3.wav" -o "output.wav" -c "config.txt"
 
 Commands for the processor need to be written out in a .txt config file.
 Config example:
 
 #command for help about commands
 help
 #$n - use n-th input audio file (count from 1)
 concate $1
 mix $2
 #mute the audio from 0 to 15 second
 mute 0 15
