#include <iostream>
#include "artist.h"
#include "buyer.h"
#include "curator.h"
#include "exhibition.h"
#include "gallery.h"
#include "artwork.h"
#include "sale.h"
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
    Sale* sale = nullptr;
    int saleID = 1;
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
        cout << "10. Display All Artworks in Gallery\n";
        cout << "11. Add Artist’s Artwork to Exhibition\n";
        cout << "12. Display All Artworks in Exhibition\n";
		cout << "13. Generate Exhibition Report\n";
		cout << "14. Buy Artwork from Exhibition (Buyer)\n";
		cout << "15. Remove Artwork from Exhibition\n";
		cout << "16. Host Exhibition in Gallery\n";
		cout << "17. Add Curator to Gallery\n";
		cout << "18. Remove Curator from Gallery\n";
		cout << "19. Search Artwork by Title\n";
		cout << "20. List All Exhibitions in Gallery\n";
        cout << "21. Generate Sale Receipt\n";
        cout << "22. Finalize Sale\n";
		cout << "23. Exit\n";
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

        case 10: {
    cout << "\nArtworks in Gallery (from Exhibition):\n";
    for (int i = 0; i < exhibition->getArtworks().getLength(); ++i) {
        Artwork* art = exhibition->getArtworks()[i];
        cout << "ID: " << art->getArtworkID()
             << " | Title: " << art->getTitle()
             << " | Year: " << art->getCreationYear()
             << " | Price: $" << art->getPrice()
             << " | Medium: " << art->getMedium()
             << " | Status: " << art->getStatus() << endl;
    }
    break;
}

        case 11: {
            int index;
            cout << "Enter index of artwork to add to exhibition: ";
            cin >> index;

            if (index >= 0 && index < artist->getArtworks().getLength()) {
                exhibition->addArtwork(artist->getArtworks()[index]);
                logger.logEvent(MyString("Artwork added to exhibition: ").append(artist->getArtworks()[index]->getTitle()));
                cout << "Artwork added to exhibition." << endl;
            }
            else {
                cout << "Invalid index." << endl;
            }
            break;
        }

        case 12: {
            cout << "\nArtworks in Exhibition:\n";
            for (int i = 0; i < exhibition->getArtworks().getLength(); ++i) {
                Artwork* art = exhibition->getArtworks()[i];
                cout << "ID: " << art->getArtworkID() << " | Title: " << art->getTitle()
                    << " | Year: " << art->getCreationYear()
                    << " | Price: $" << art->getPrice() << endl;
            }
            break;
        }
        case 13: {
            cout << "\n=== Exhibition Report ===\n";
            cout << "Exhibition Name: " << exhibition->getName() << endl;
            cout << " Start Date: " << exhibition->getStartDate() << endl;
			cout << " End Date: " << exhibition->getEndDate() << endl;
            cout << "Total Artworks: " << exhibition->getArtworks().getLength() << endl;

            float totalValue = 0;
            for (int i = 0; i < exhibition->getArtworks().getLength(); ++i) {
                Artwork* art = exhibition->getArtworks()[i];
                totalValue += art->getPrice();
            }

            cout << "Estimated Total Value: $" << totalValue << endl;
            break;
        }

        case 14: {
            if (!sale) {
                MyString date("2025-06-15"); 
                sale = new Sale(saleID++, date, buyer);
                cout << "Sale started for buyer: " << buyer->getName() << endl;
            }
            exhibition->displayAllPaintings();
            int id;
            cout << "Enter Artwork ID to buy: ";
            cin >> id;

            Artwork* selected = nullptr;
            Dynamic_array<Artwork*>& list = exhibition->getArtworks();

            for (int i = 0; i < list.getLength(); ++i) {
                if (list[i]->getArtworkID() == id) {
                    selected = list[i];
                    break;
                }
            }

            if (selected) {
                float price = selected->getPrice(); 
                sale->addArtwork(selected, price);
            }
            else {
                cout << "Artwork ID not found in exhibition.\n";
            }

            break;
        }

        case 15: {
            int artID;
            cout << "Enter Artwork ID to remove from exhibition: ";
            cin >> artID;
            exhibition->removeArtwork(artID);
            break;
        }
        case 16:
            gallery.hostExhibition(exhibition);
            break;
        case 17: {
            int cid;
            MyString name, email;
            cout << "Enter Curator ID: ";
            cin >> cid;
            cout << "Enter Curator Name: ";
            cin >> name;
            cout << "Enter Email: ";
            cin >> email;
            Curator* newCurator = new Curator(cid, name, email, "01/01/2000", 1, "modern art");
            gallery.addCurator(newCurator);
            break;
        }
        case 18: {
            int cid;
            cout << "Enter Curator ID to remove: ";
            cin >> cid;
            gallery.removeCurator(cid);
            break;
        }
        case 19: {
            MyString searchTitle;
            cout << "Enter Artwork Title to search: ";
            cin >> searchTitle;
            gallery.searchArtwork(searchTitle);
            break;
        }
        case 20:
            gallery.listAllExhibitions();
            break;
        case 21: {
            if (sale) {
                sale->generateReceipt();
            }
            else {
                cout << "No sale in progress.\n";
            }
            break;
        }
        case 22: {
            if (sale) {
                try {
                    sale->finalizeSale();
                    delete sale;
                    sale = nullptr;
                }
                catch (const NullReferenceException& ex) {
                    logger.logError(ex.getMessage());
                }
            }
            else {
                cout << "No sale to finalize.\n";
            }
            break;
        }


		case 23:
			cout << "Exiting program." << endl;
			break;
        default:
            cout << "Invalid choice." << endl;
        }

    } while (choice != 23);

    delete artist;
    delete buyer;
    delete curator;
    return 0;
}


	// this is how to call browse artwork func buyer.browseArtworks(gallery.getAllArtworks());

	//to sort artworks
	// Sort by title (A-Z)
	//exhibition.sortArtworksBy([](Artwork* a, Artwork* b) {
	//	return a->getTitle().is_less(b->getTitle());
	//	});

	//// Sort by price (low to high)
	//exhibition.sortArtworksBy([](Artwork* a, Artwork* b) {
	//	return a->getPrice() < b->getPrice();
	//	});

	//// Sort by creation year (oldest to newest)
	//exhibition.sortArtworksBy([](Artwork* a, Artwork* b) {
	//	return a->getCreationYear() < b->getCreationYear();
	//	});

// try catch blocks
	/*try {
		artist.addArtwork(artwork);
	}
	catch (const DuplicateArtworkException& ex) {
		logger.logError("Duplicate artwork caught in main: " + MyString(ex.getArtworkID()));
	}

	try {
		artwork->loadImageFromFile("somepath.jpg");
	}
	catch (const ImageLoadException& ex) {
		logger.logError("Image load failed: " + ex.getFilePath());
	}

	try {
		curator->organizeExhibition(exhibition);
	}
	catch (const NullReferenceException& ex) {
		logger.logError("Null reference in exhibition: " + ex.getMessage());
	}

	try {
		exhibition->saveToBinary("output.bin");
	}
	catch (const FileIOException& ex) {
		logger.logError("Failed to save exhibition: " + ex.getFileName());
	}
	*/


	//try {
	//	// all main logic
	//}
	//catch (const Exception& ex) {
	//	logger.logError("Unhandled exception: " + ex.getMessage());
	//}
