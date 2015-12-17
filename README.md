# iot-mediatek-linkIt

Step1: (aspnet5)
  a. change the azure storage credential in iotcontroller
  b. publish it to your cloud.
  c. use the address in nodejs app
  
Step2: (nodejs app)
  a. Replace the ipaddress in index.js
  b. Navigate to iotapp published in local sever (raspberry pi or orange pi or your pc)
  c. Start app in debug mode $ DEBUG=iotapp:* node index.js
  c. use the local address in mediatekrx.ino

Step1: (media Tek ino)
  a. Open MediaTekRx.ino and put your wifi password and local server ip
  b. Burn the MediaTekRx.ino to MediaTek - Linkt It
  

