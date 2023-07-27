
#include "StatePerson.h"

String StatePerson::checkBloodPressure(float systolic, float diastolic)
{

    if (systolic < 120 && diastolic < 80)
        return "NORMAL";
    else if ((systolic > 120 && systolic < 129) && (diastolic < 80))
        return "ELEVATED";
    else if ((systolic >= 130 && systolic < 139) || (diastolic > 80 && diastolic < 89))
        return "HYPERTENSION_STAGE_1";
    else if ((systolic >= 140) || (diastolic >= 90))
        return "HYPERTENSION_STAGE_2";
    else if ((systolic > 180) || (diastolic > 120))
        return "HYPERTENSION_CRISIS";
    else
        return "NONE";
}

String StatePerson::checkBloodOxygen(int age, float spo2)
{

    if ((age < 70) && (spo2 >= 95 && spo2 <= 100))
        return "NORMAL";
    else if ((age >= 70) && (spo2 >= 94.9 && spo2 <= 95.999))
        return "NORMAL";
    else
        return "ABNORMAL";
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
    else
        return "ABNORMAL";
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
