# Flood Detection

Our ESP32 flood detection capstone project.

## Get a copy of the repo

Using [GitHub Desktop](https://desktop.github.com/):

1. Install GitHub Desktop and sign in to GitHub.
2. Go to **File > Clone repository > URL** and paste:
   ```text
   https://github.com/WizardInDminor/flood-detection.git
   ```
3. Choose where to save it on your computer and click **Clone**.

To get the latest changes later, click **Fetch origin**, then **Pull origin** if it appears.

If you already use Git, you can clone it from a terminal instead:

```sh
git clone https://github.com/WizardInDminor/flood-detection.git
```

## Open it in Arduino IDE

Open the **`flood-detection` folder inside the repo** by opening `flood-detection/flood-detection.ino` in Arduino IDE. Keep the `.h` and `.cpp` files in that same folder so the IDE includes them when it builds.

You'll need the **esp32** board package by Espressif Systems and the **U8g2** library installed through Boards Manager and Library Manager. Select your ESP32 board and port, then verify or upload the sketch.

## Open the Doxygen site

1. Install [Doxygen](https://www.doxygen.nl/download.html) and make sure it's on your PATH.
2. Open a terminal in the repo's top-level folder (the one with `Doxyfile`) and run:
   ```sh
   doxygen Doxyfile
   ```
3. Open `build/doxygen/html/index.html` in your browser using the following commands:  
  
  **On WINDOWS:**
  ```sh
  start build/doxygen/html/index.html
  ```
  **On MAC:**
  ```sh
  open build/doxygen/html/index.html
  ```

The generated site isn't included in the repo. Run the command again after code changes to update it.
