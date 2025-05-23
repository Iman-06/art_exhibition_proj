# art_exhibition_proj
Project Description:
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
