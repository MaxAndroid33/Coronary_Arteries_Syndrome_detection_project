
#ifndef CONNECTION_H
#define CONNECTION_H

#include <Arduino.h>

#endif

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Patient Data</title>


</head>

<body>
    <style>
        :root {
            --bg-color: #0c0c0c;
            --bg-color-100: #1d1531;
            --bg-color-200: #2d2b30;
            --bg-color-300: #cccccc42;

            --txt-color: #9d9da3;

            --primary-color: #1d1e1b;
            --primary-color-100: #a5d726;

            --secondary-color: #26ca58;
            --accent-color: #34cd39;

            --bg-100: #000130;

            --warnning-color: #890909;
        }

        * {
            box-sizing: border-box;
        }

        body {
            background-color: var(--bg-color);
            color: var(--txt-color);
        }

        .main__container {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(min(400px, 100%), 1fr));

            align-content: space-around;
            gap: 2rem;

            margin-top: 3rem;
            margin-inline: auto;
            /* max-width: 1200px; */

        }


        label {
            display: flex;
            padding-top: 4%;
            flex-direction: row;
            justify-content: space-between;
            align-items: center;
        }

        input {
            display: block;

            width: 100%;
            padding: 0.5rem;

            border-radius: 10px;
            border: none;
            outline: none;
            cursor: pointer;
            background-color: #cccccc42;
            color: var(--txt-color);
        }

        #savebtn {
            background-color: #3de31342 !important;
        }

        #removebtn {
            background-color: #e3131342 !important;
        }

        #savebtn:hover {

            background-color: #3de313 !important;
            color: #fefefe;
        }

        #removebtn:hover {

            background-color: #e31313e8 !important;
            color: #fefefe;

        }

        h1 {
            text-align: center;
        }

        h2 {
            font-size: 1.2rem;
        }


        .container {
            display: grid;
            place-content: center;
            gap: 0.5rem;

            grid-template-columns: min(100%, 300px);
        }

        .d-flex {
            display: flex;
            place-content: center;
            align-items: center;
            gap: 0.5rem;

            position: relative;
        }

        .accent {
            color: var(--accent-color);
        }
    </style>
    <header>
        <h1>Patient <span class="accent">Profile</span> </h1>
    </header>
    <form action='/save' method='post'>
        <main>

            <div class="main__container">
                <div class="left">
                    <div class="container">
                        <h2>Parson Data</h2>
                        <label>User ID: </label>
                        <input type='number' name='id' required><br></label>
                        <fieldset data-role="controlgroup">

                            <legend>Choose Your Gender:</legend>
                            <label for="male">Male
                                <span><input type="radio" name="gender" id="male" value="male" checked></span></label>
                            <label for="female">Female
                                <span><input type="radio" name="gender" id="female" value="female"></span></label>
                        </fieldset><br>
                        <label>Age:</label> <input type='number' name='age' required><br>
                        <label>Date:</label><input type='date' name='date' required><br>

                    </div>
                </div>


                <div class="right">
                    <div class="container">
                        <h2>General Data</h2>
                        <label>Systematic Blood Pressure :</label>
                        <input type='number' name='SBP' required>
                        <label>Diastolic Blood Pressure :</label>
                        <input type='number' name='DSP' required>
                        <label>Normal Heart Rate :</label>
                        <input type='number' name='NHR' required>
                        <label>Normal Body Temperature :</label>
                        <input type='number' name='NBT' required>
                        <label>Normal SpO2 :</label>
                        <input type='number' name='NSPO' required> 
                    </div>
                    <dir></dir>
                </div>
                <div class="left">
                    <div class="container">
                        <h2>Optional</h2>
                        <label>Cholesterol
                            <span><input type="checkbox" name="chol" id="SIC" value="cholesterol"> </span></label>
                        <label>Hypertension
                            <span> <input type="checkbox" name="hyper" id="SIC" value="Hypertension"></span></label>
                        <label>Diabetes
                            <span> <input type="checkbox" name="diabetes" id="SIC" value="diabetes"></span></label>
                        <label>OverWeight
                            <span><input type="checkbox" name="overw" id="SIC" value="overweight"></span></label>
                        <label>Smoking
                            <span><input type="checkbox" name="smok" id="SIC" value="smoking"></span></label>
                        <label>Alcohol
                            <span><input type="checkbox" name="alcoh" id="SIC" value="alcohol"></span></label>


                    </div>

                </div>
            </div>
            <div ><br></div>
        </main>
        <div class="container">

            <br><input type='submit' value='Save' id="savebtn"><br>
            

        </div>
    </form>
    <div class="container">
    <form action='/remove' method='post'>
        <br><input type='submit' value='Remove All Data ' id="removebtn">
    </form>
</div>
</body>

</html>

)rawliteral";