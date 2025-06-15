README - Art Exhibition Management System

This is my semester project made in C++. It is a console-based management system for handling an art exhibition. It uses object-oriented programming concepts like inheritance, polymorphism, file handling, exception handling, and custom classes.

Features:
Add artworks with image loading (using OpenCV)

Organize exhibitions and sort artworks

Add/remove curators

Host exhibitions in a gallery

Buyers can view and buy artworks

Sale receipts and binary file saving/loading

How to Run:
Make sure OpenCV is properly set up (I used opencv_world470d.dll and related files).

Place artwork1.jpeg, artwork2.jpeg, artwork3.jpeg inside:

bash
Copy
Edit
project_folder/art_exhibition_proj/images/
Open the project in Visual Studio and build it (x64 Debug).

Run the executable or use main.cpp to test all menu features.

Notes:
All strings are handled using a custom MyString class.

Images are displayed in a pop-up using OpenCV.

Binary data is saved in exhibition_data.bin in the same folder.

Project Description - Eval 1:
This project helps manage artists, their unique artworks, and public exhibitions. It allows users to:
Create artists and add artworks (with image files using OpenCV)
Organize exhibitions and display all artwork images
Leave and view reviews on artworks
Save and load exhibition data using binary files
Log important events and handle errors using custom exceptions

In real life, some objects (like artworks and their artists) are closely connected, but in my project, I chose not to model them with strict ownership (like composition) to keep the design flexible. However, I made the relationships between Artist–Artwork and Artwork–Review bidirectional so that I could implement useful features like listing all artworks by an artist or viewing all reviews on an artwork.
UML
![image](https://github.com/user-attachments/assets/9ff3ab43-ffe2-4bde-90f4-504103bd1644)

FLOWCHART
https://www.mermaidchart.com/raw/ed07c61f-d8f5-4a3e-b53e-d171d0677ca5?theme=light&version=v0.1&format=svg
