#include <iostream>
#include "artist.h"
#include "buyer.h"
#include "curator.h"
#include "exhibition.h"
#include "gallery.h"
#include "logger.h"
#include "fileIOException.h"
#include "imageLoadException.h"
#include "nullReferenceException.h"
#include "duplicateArtworkException.h"
using namespace std;

int main() {
    Logger logger("log.txt");
    Artist* artist = new Artist(1, MyString("Van Gogh"), MyString("vangogh@email.com"),"09/08/1180",1,"italy","oil painting");
    Buyer* buyer = new Buyer(101, MyString("John Doe"), MyString("john@email.com"),"11/08/2000",1,"address");
    Curator* curator = new Curator(201, MyString("Emily Curator"), MyString("emily@email.com"), "18/08/2000",1,"abstract art");
    Exhibition* exhibition = new Exhibition(1, MyString("Impressionist Art"), MyString("2025-01-01"), MyString("2025-12-31"), curator);
	Gallery gallery(1, "Art Gallery", MyString("123 Art St"), 10);
    gallery.addCurator(curator);
    int choice;
    do {
        cout << "\n----- Art Exhibition Management Menu -----\n";
        cout << "1. Add Artwork to Artist\n";
        cout << "2. Browse Artworks (Buyer)\n";
        cout << "3. View Artwork Image (Buyer)\n";
        cout << "4. Organize Exhibition (Curator)\n";
        cout << "5. Sort Artworks by Title\n";
        cout << "6. Sort Artworks by Price\n";
        cout << "7. Sort Artworks by Year\n";
        cout << "8. Save Exhibition to Binary\n";
        cout << "9. Load Exhibition from Binary\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            try {
                static int idCounter = 1;

                MyString idStr(idCounter);
                MyString base("Artwork ");
                MyString title = base.concat(idStr);

                MyString medium("Oil on Canvas");
                float price = 1000.0f + idCounter * 100;
                int year = 1880 + idCounter;

                MyString prefix("artwork");
                MyString ext(".jpeg");
                MyString imageName = prefix.concat(idStr).concat(ext);
                Artwork* art = new Artwork(idCounter, title, price, medium, year, artist,imageName);
                art->setImagePath(imageName);
                art->loadImageFromFile(imageName);
                artist->addArtwork(art);
                logger.logEvent(MyString("Artwork added: ").append(title));

                idCounter++;

            }
            catch (const DuplicateArtworkException& ex) {
                logger.logError(ex.getMessage());
            }
            catch (const ImageLoadException& ex) {
                logger.logError(ex.getMessage());
            }
            break;
        }
        case 2:
            buyer->browseArtworks(artist->getArtworks());
            break;

        case 3: {
            int index;
            cout << "Enter index of artwork to view (0, 1, or 2): ";
            cin >> index;
            if (index >= 0 && index < artist->getArtworks().getLength()) {
                artist->getArtworks()[index]->displayImage();
            }
            else {
                cout << "Invalid index." << endl;
            }
            break;
        }

        case 4:
            try {
                curator->organizeExhibition(exhibition);
            }
            catch (const NullReferenceException& ex) {
                logger.logError(ex.getMessage());
            }
            break;

        case 5:
            exhibition->sortArtworksBy([](Artwork* a, Artwork* b) {
                return a->getTitle().is_less(b->getTitle());
                });
            break;

        case 6:
            exhibition->sortArtworksBy([](Artwork* a, Artwork* b) {
                return a->getPrice() < b->getPrice();
                });
            break;

        case 7:
            exhibition->sortArtworksBy([](Artwork* a, Artwork* b) {
                return a->getCreationYear() < b->getCreationYear();
                });
            break;

        case 8:
            exhibition->saveToBinary(MyString("exhibition_data.bin"));
            break;

        case 9:
            exhibition->loadFromBinary(MyString("exhibition_data.bin"));
            break;

        case 10:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice." << endl;
        }

    } while (choice != 10);

    delete artist;
    delete buyer;
    delete curator;
    return 0;
}





//#include "Artwork.h"
//#include "Artist.h"
//#include "My_string.h"
//#include "ImageLoadException.h"
//#include <iostream>
//#include <opencv2/opencv.hpp>
//using namespace cv;
//int main() {
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//	////cout << "Hello, World!" << endl;
//	//std::string path = "C:\\Users\\LENOVO\\Pictures\\sample.png"; // ✅ Change to your image path
//
//	//// Load the image from file
//	//Mat image = imread(path);
//
//	//// Check if the image loaded successfully
//	//if (image.empty()) {
//	//	std::cout << "Failed to load image from: " << path << std::endl;
//	//	return -1;
//	//}
//
//	//// Optional: Resize the image to fit better on screen
//	//Mat resizedImage;
//	//resize(image, resizedImage, Size(800, 600)); // Resize to 800x600 pixels
//
//	//// Create a resizable window
//	//namedWindow("Test Image", WINDOW_NORMAL);
//
//	//// Display the image
//	//imshow("Test Image", resizedImage);
//
//	//// Wait until a key is pressed
//	//waitKey(0);
//
//	Artist artist1(1, "van gogh", "email@123","09/08/1990",1,"italy","oil painting");
//	Artwork art(1, "image", 100.0, "Oil on Canvas", 2023, nullptr, MyString("artwork1.jpg"));
//
//		// Use the actual image file name (only the file name, not the full path)
//		MyString imageFileName("artwork1.jpeg"); // replace with your actual file in /images/
//
//		try {
//			art.loadImageFromFile(imageFileName);
//			art.displayImage();
//		}
//		catch (const ImageLoadException& ex) {
//			std::cout << "Exception: " << ex.getMessage() << std::endl;
//		}
//
//		return 0;
//	}
//
//
//	// this is how to call browse artwork func buyer.browseArtworks(gallery.getAllArtworks());
//
//	//to sort artworks
//	// Sort by title (A-Z)
//	//exhibition.sortArtworksBy([](Artwork* a, Artwork* b) {
//	//	return a->getTitle().is_less(b->getTitle());
//	//	});
//
//	//// Sort by price (low to high)
//	//exhibition.sortArtworksBy([](Artwork* a, Artwork* b) {
//	//	return a->getPrice() < b->getPrice();
//	//	});
//
//	//// Sort by creation year (oldest to newest)
//	//exhibition.sortArtworksBy([](Artwork* a, Artwork* b) {
//	//	return a->getCreationYear() < b->getCreationYear();
//	//	});
//
//
//	//if artwork is added
////	logger.logEvent("Artwork created for artist: " + artist.getName());
//	// if sale is finalized
//	//	logger.logEvent("Sale finalized with buyer: " + buyer.getName());
//
//
//	/*try {
//		artist.addArtwork(artwork);
//	}
//	catch (const DuplicateArtworkException& ex) {
//		logger.logError("Duplicate artwork caught in main: " + MyString(ex.getArtworkID()));
//	}
//
//	try {
//		artwork->loadImageFromFile("somepath.jpg");
//	}
//	catch (const ImageLoadException& ex) {
//		logger.logError("Image load failed: " + ex.getFilePath());
//	}
//
//	try {
//		curator->organizeExhibition(exhibition);
//	}
//	catch (const NullReferenceException& ex) {
//		logger.logError("Null reference in exhibition: " + ex.getMessage());
//	}
//
//	try {
//		exhibition->saveToBinary("output.bin");
//	}
//	catch (const FileIOException& ex) {
//		logger.logError("Failed to save exhibition: " + ex.getFileName());
//	}
//	*/
//
//
//	//try {
//	//	// all main logic
//	//}
//	//catch (const Exception& ex) {
//	//	logger.logError("Unhandled exception: " + ex.getMessage());
//	//}
//
//
//	//return 0;
////}