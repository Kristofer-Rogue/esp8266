//=========================================
//HTML + CSS + JavaScript codes for webpage
//=========================================
const char webpageCode[] =
R"=====(
<!DOCTYPE html>
<html>
<!------------------------------C S S--------------------------------->

<!----------------------------H T M L--------------------------------->
<body>
  
<!---------------------------JavaScript------------------------------->
<div>Teachable Machine Audio Model</div>
<button type="button" onclick="init()">Start</button>
<div id="label-container"></div>
<script src="https://cdn.jsdelivr.net/npm/@tensorflow/tfjs@1.3.1/dist/tf.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/@tensorflow-models/speech-commands@0.4.0/dist/speech-commands.min.js"></script>

<script type="text/javascript">
    // more documentation available at
    // https://github.com/tensorflow/tfjs-models/tree/master/speech-commands

    // the link to your model provided by Teachable Machine export panel
    const URL = "https://teachablemachine.withgoogle.com/models/FyK4-zZcB/";

    async function createModel() {
        const checkpointURL =  URL + "model.json"; // model topology
        const metadataURL =  URL + "metadata.json"; // model metadata

        const recognizer = speechCommands.create(
            "BROWSER_FFT", // fourier transform type, not useful to change
            undefined, // speech commands vocabulary feature, not useful for your models
            checkpointURL,
            metadataURL);

        // check that model and metadata are loaded via HTTPS requests.
        await recognizer.ensureModelLoaded();

        return recognizer;
    }
    function send(led_sts) 
{
  
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("state").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "led_set?state="+led_sts, true);
  xhttp.send();
}
    async function init() {
        const recognizer = await createModel();
        const classLabels = recognizer.wordLabels(); // get class labels
        const labelContainer = document.getElementById("label-container");
        for (let i = 0; i < classLabels.length; i++) {
            labelContainer.appendChild(document.createElement("div"));
        }

        // listen() takes two arguments:
        // 1. A callback function that is invoked anytime a word is recognized.
        // 2. A configuration object with adjustable fields
        recognizer.listen(result => {
            const scores = result.scores; // probability of prediction for each class
            // render the probability scores per class
            if (Math.max.apply(null, result.scores) == result.scores[0])
              send(0);
              if (Math.max.apply(null, result.scores) == result.scores[1])
              send(1);
              if (Math.max.apply(null, result.scores) == result.scores[2])
              send(2);
            for (let i = 0; i < classLabels.length; i++) {
                const classPrediction = classLabels[i] + ": " + result.scores[i].toFixed(2);
                labelContainer.childNodes[i].innerHTML = classPrediction;
                
               
            }
        }, {
            includeSpectrogram: true, // in case listen should return result.spectrogram
            probabilityThreshold: 0.75,
            invokeCallbackOnNoiseAndUnknown: true,
            overlapFactor: 0.50 // probably want between 0.5 and 0.75. More info in README
        });

        // Stop the recognition in 5 seconds.
        // setTimeout(() => recognizer.stopListening(), 5000);
    }
</script>


</body>
</html>
)=====";
