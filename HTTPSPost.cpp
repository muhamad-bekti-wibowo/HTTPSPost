/*
  27 July 2023 developed by Muhammad Bekti Wibowo

  Program ini dikembangkan oleh Muhammad Bekti Wibowo untuk pengembangan project dengan HTTPS.
  khususnya untuk project saya di https://mbw-projects.000webhostapp.com/
  Jika saya masih belum bisa membeli server sendiri. dukung saya untuk membeli server di https://saweria.co/FastProjectMBW

  Program Sebelumnya Dibuat Oleh Rui Santos
  Lengkapi detail proyek di Lengkapi detail proyek di https://RandomNerdTutorials.com/
  Izin dengan ini diberikan, tanpa biaya, kepada siapa pun yang mendapatkan salinan perangkat lunak ini dan file dokumentasi terkait.
  Pemberitahuan hak cipta di atas dan pemberitahuan izin ini harus menyertakan semua salinan atau sebagian besar dari Perangkat Lunak.

  Referensi
  ~ https://randomnerdtutorials.com/esp32-https-requests/
  ~ https://randomnerdtutorials.com/esp32-cam-post-image-photo-server/
  ~ https://www.geeksforgeeks.org/http-headers-content-type/
  ~ https://circuits4you.com/2019/02/08/esp8266-nodemcu-https-secured-post-request/

  This program was developed by Muhammad Bekti Wibowo for project development with HTTPS.
  especially for my project at https://mbw-projects.000webhostapp.com/
  If I still can't buy my own server. support me to buy server at https://saweria.co/FastProjectMBW

  Previous Program Created By Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/
  Permission is hereby granted, without charge, to anyone who obtains a copy of this software and associated documentation files.
  The above copyright notice and this permission notice must include all copies or a large portion of the Software.

  Reference
  ~ https://randomnerdtutorials.com/esp32-https-requests/
  ~ https://randomnerdtutorials.com/esp32-cam-post-image-photo-server/
  ~ https://www.geeksforgeeks.org/http-headers-content-type/
  ~ https://circuits4you.com/2019/02/08/esp8266-nodemcu-https-secured-post-request/
*/
#include "HTTPSPost.h"
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#define Equipment "ESP8266"
#elif defined(ESP32)
#include <WiFi.h>
#define Equipment "ESP32"
#else
#error "Please check that the microcontroller you are using,can only be used on ESP8266 or ESP32 only"
#endif
HTTPSPost::HTTPSPost(String ServerName_, String ServerPath_ )
{
    ServerPath = ServerPath_;
    ServerName = ServerName_;
   
}
String HTTPSPost::send(String data, char x)
{
    // Serial.printf("Using fingerprint '%s'\n", fingerprint);
    // httpsClient.setFingerprint(fingerprint);
    // httpsClient.setTimeout(15000); // 15 Seconds
    client.setInsecure();
    if (client.connect(ServerName.c_str(), 443))
    {
        client.println("POST " + ServerPath + " HTTP/1.1");
        client.println("Host: " + ServerName);
        client.println("Content-Type: application/x-www-form-urlencoded");
        client.println("Content-Length: " + String(data.length()));
        client.println();
        client.println(String("Equipment=") + Equipment + String("&") + data);
        client.println();
        client.println("Connection: close");
        client.readStringUntil(x);
        String Reply = "";
        int value = client.available();
        char c = client.read();
        while (value)
        {
            c = client.read();
            Reply += String(c);

            if (Reply.indexOf("<!--END-->") != -1)
            {
                value = 0;
            }
        }
        Serial.println("Balasan dari Website : \n" + Reply);
        client.stop();
        return "Balasan dari Website : \n" + Reply;
    }
    return "Pengiriman data gagal";
}