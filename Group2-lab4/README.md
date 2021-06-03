# CS307-Assignment-4
Rashika(b18081)
Kalyani(b18063)


Q1. Design a file transfer application.
How to run?
1. client.c has code for client VM.
2. server.c has code for server VM.
3. compile server.c by using “gcc server.c -o server”
4. run the server using “./server”.
5. compile client.c by using “gcc client.c -o client”
6. Enter the filename to be downloaded on client side.
7. It is saved with 'Saved-' + filename in the client machine..
8. Check for its size and it's a reliable connection.


Q2. Error Control
How to run?
1. q2.c has code for this question.
2. Now compile q2.c by using “gcc q2.c -o q2"
3. Now run the server on terminal using “./q2 server”
5. Now run the client on another tab in the terminal using “./q2 client”
6. Enter the key for crc algorithm. on client side (length 5).
7. Now server will automatically generate a random string of '0' and '1' and will apply crc algorithm on it, then it'll send that message to client & client will again apply crc on it using the key entered in step 6.
8. Client will tell whether there is error present in the message received from server or not.

Q3. results are present in the report.
