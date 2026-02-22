# MirrorPaint

## C++/SFML mirrored painting program

<img width="1728" height="1117" alt="Screenshot 2026-02-12 at 5 43 14 PM" src="https://github.com/user-attachments/assets/c55ede89-0ba5-4a97-bc52-1db7b5f1cb38" />
<img width="1728" height="1728" alt="161101621036863011" src="https://github.com/user-attachments/assets/d7a81e49-5be7-48a5-bf8f-85de43c64819" />

### ABOUT THE PROJECT
In the mid-80's I got loads of childish satisfaction making black-and-white mirror drawings using SuperPaint on a Mac Plus. Learning programming as an adult, executing a mirror paint program of my own was one of the first challenges to present itself to my mind. As with several other of my existing C++ projects, my experiment originated in my pre-C++ Python days. I accomplished the mirroring stroke there with no bells and whistles, and moved along to more pressing things. A couple years later, I came back and ported the idea to C++, souping up the feature list significantly. 

My children's enjoyment and education fueled the renovation of this program; I didn't have unlimited time to craft and polish it according to my every whim, but there was a certain range of functionalities that I wanted to implement both for their artistic experience and also for the intrigue of successfully coding certain effects. 

The program features a homemade color picker, customizable axes along which to mirror the drawing (pinwheel, snowflake, pick-and-choose from the standard 16-point reflections), and several stroke styles, some continuous and some periodic (like a continuous path of repeating shapes). A fill bucket can be used mirror-fashion, and limited random color deviation can be used to create interest with certain brush types. There are basic mechanisms for undoing the last stroke and for saving the current canvas to a file.

Except when noted, all the graphics in my programs are created by me, some programmatically and some as pixel art. The majority of sound effects that I use are from the public domain. 

### FILE DESCRIPTIONS
* **sfmlApp:**  Implements `main()` and the abstract app
* **mirrorpaint:**  Implements primary graphical elements, editor handling, and drawing logic
* **ColorPicker:**  Class for the color picker
* **AxisPicker:**  Class for the pickers of which axes to reflect on
* **editorcomponents:**  Abstractions and odd and ends like DrawingMode, BrushButton, etc.
  
(From my "reusable modules" repo: https://github.com/johnnywz00/SFML-shared-headers)
* **jwz:**  C++ utility functions, #defines, shortcuts
* **jwzsfml:**  Like above, but SFML-specific
* **resourcemanager:**  Static class for accessing resource files globally
* **timedeventmanager:**  Manages fuses/daemons, delayed callbacks

### BUILDING INSTRUCTIONS
Ready-made program files are available on the Releases page of this repository, with versions for MacOS, Windows, and Linux. NO INSTALLATION NECESSARY: just download and double-click. If your OS isn't supported by the pre-made versions, or if you have other reasons for building from source:
- Clone this repository, and navigate to the root folder of that clone in a terminal window.
- Run:
<pre>
   cmake -B build
   cmake --build build --parallel
</pre>
