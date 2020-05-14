var Module = {
    onRuntimeInitialized: function() {
        // Hide 'Loading...' text when wasm initialized.
        document.querySelector('#loading').style.display = 'none';
        // Show canvas.
        document.querySelector('#window').style.display = 'block';
    },
    canvas: document.querySelector('#canvas')
};

function loadScript() {
    console.log("Loading js...");

    var xhr = new XMLHttpRequest();
    var script = document.createElement("script");

    xhr.open("GET", "sdl_tutorial.js", true);
    xhr.onload = function () {
        if (xhr.readyState === 4) {
            if (xhr.status === 200) {
                script.text = xhr.response;
                document.body.appendChild(script);
            }
        } else {
            console.error(xhr.response);
        }
    };

    xhr.send();
};

// Return a canvas parent size to fill all the space in the window.
// Canvas parent element style size is 100% of window.
function getCanvasParentWidth() {
    return Module.canvas.parentElement.offsetWidth;
}

function getCanvasParentHeight() {
    return Module.canvas.parentElement.offsetHeight;
}

function onResize() {
    var ratio = window.devicePixelRatio || 1;
    var width = getCanvasParentWidth() * ratio;
    var height = getCanvasParentHeight() * ratio;

    Module.setCanvasSize(width, height);
}

var resizeTimeoutId;

window.onload = function() {
    // Check if WebAssembly supported
    if (typeof WebAssembly === 'object') {
        document.querySelector('#wasm').style.display = 'none';
        loadScript();
    }
    else {
        document.querySelector('#loading').style.display = 'none';
    }

    // Resize canvas when window resized.
    // Event will be handled in 100ms to prevent excess calls.
    window.addEventListener('resize', function() {
        clearTimeout(resizeTimeoutId);
        resizeTimeoutId = setTimeout(onResize, 100);
    });
}