# serial_linux_testing
Serial_Communication testing. Mostly used for SDSL and will be used eventually on 

The Serial Transmission file is used sending and requesting pictures from the camera end.
The Serial Receiver file is used for receving the commands from the transmission end.

compile commands:
either "make build_receiver" (for receiver) or "make build_issuer" for the issuer

issuer refers to the station with the camera hooked up to (i.e streaming images to receiver)

syntax:

./picture_(issuer or receiver) [serial_path]


#Testing svn
