
#include "StatePerson.h"

String StatePerson::checkBloodPressure(float systolic, float diastolic)
{

    if (systolic < 120 && diastolic < 80)
        return "NORMAL";
    else if ((systolic > 120 && systolic < 129) && (diastolic < 80))
        return "ELEVATED";
    else if ((systolic >= 130 && systolic < 139) || (diastolic > 80 && diastolic < 89)){
        dangerLevel =stage1;
        return "HYPERTENSION_STAGE_1";
    }
    else if ((systolic >= 140) || (diastolic >= 90)){
        dangerLevel =stage2;
        return "HYPERTENSION_STAGE_2";
    }
    else if ((systolic > 180) || (diastolic > 120)){
        dangerLevel =stage3;
        return "HYPERTENSION_CRISIS";
    }
    else
        return "NONE";
}

String StatePerson::checkBloodOxygen(int age, float spo2)
{

    if ((age < 70) && (spo2 >= 95 && spo2 <= 100))
        return "NORMAL";
    else if ((age >= 70) && (spo2 >= 94.9 && spo2 <= 95.999))
        return "NORMAL";
    else{
        dangerLevel =oxygen;
        return "ABNORMAL";
    }
}

String StatePerson::checkHeartRate(int age, float heartRate)
{
    if ((age >= 3 && age <= 5) && (heartRate >= 80 && heartRate <= 120))
        return "NORMAL";
    else if ((age >= 6 && age <= 10) && (heartRate >= 70 && heartRate <= 110))
        return "NORMAL";
    else if ((age >= 11 && age <= 14) && (heartRate >= 60 && heartRate <= 105))
        return "NORMAL";
    else if ((age > 14) && (heartRate >= 60 && heartRate <= 100))
        return "NORMAL";
    else{
        dangerLevel =heart;
        return "ABNORMAL";
    }
}

String StatePerson::checkBloodPressure(int age, String gender)
{

    if ((age >= 18 && age <= 39) && "male")
        return "119/70 mmHg";
    else if ((age >= 18 && age <= 39) && "female")
        return "110/68 mmHg";
    else if ((age >= 40 && age <= 59) && "male")
        return "124/77 mmHg";
    else if ((age >= 40 && age <= 59) && "female")
        return "122/74 mmHg";
    else if ((age >= 60) && "male")
        return "133/69 mmHg";
    else if ((age >= 60) && "female")
        return "139/68 mmHg";
    else
        return "NO Data";
}

String StatePerson::ageLevel(int age)
{
    if (age <= 2)
        return "baby";
    else if (age > 2 && age <= 16)
        return "child";
    else if (age > 16 && age <= 30)
        return "adult";
    else if (age > 30 && age <= 45)
        return "middle_aged";
    else if (age > 45)
        return "old_aged";
    else
        return "NONE";
}

void StatePerson::sendSms(String message, String number,SoftwareSerial &mySerial)
{
    mySerial.println("AT"); // Once the handshake test is successful, it will back to OK
    updateSerial(mySerial);

    mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
    updateSerial(mySerial);
    mySerial.println("AT+CMGS=\"" + number + "\""); // change ZZ with country code and xxxxxxxxxxx with phone number to sms
    updateSerial(mySerial);
    mySerial.print(message); // text content
    updateSerial(mySerial);
    mySerial.write(26);
}

void StatePerson::alertDoctor(String number ,SoftwareSerial &mySerial)
{
    switch (dangerLevel)
    {
    case stage1:
        sendSms("Patient has HYPERTENSION_STAGE_1",number,mySerial);
        break;
    case stage2:
        sendSms("Patient has HYPERTENSION_STAGE_2",number,mySerial);
        break;
    case stage3:
        sendSms("Patient has HYPERTENSION_CRISIS",number,mySerial);
        break;
    // case oxygen:
    //     sendSms("Patient's Blood Oxygen is not Normal",number,mySerial);
    //     break;
    // case heart:
    //     sendSms("Patient's Heart Rate is not Normal",number,mySerial);
        // break;
    
    default:
        break;
    }
    Serial.println(dangerLevel);
}
void StatePerson::alert()
{
    if(dangerLevel ==2)
    while(true){
        Serial.println("Alert !!");
    };
}

void StatePerson::updateSerial(SoftwareSerial &mySerial)
{
    delay(500);
    // while (Serial.available())
    // {
    //     mySerial.write(Serial.read()); // Forward what Serial received to Software Serial Port
    // }
    while (mySerial.available())
    {
        Serial.write(mySerial.read()); // Forward what Software Serial received to Serial Port
    }
}



void StatePerson::begin(SoftwareSerial &mySerial)
{  
    mySerial.begin(9600);
    delay(4000);
}
