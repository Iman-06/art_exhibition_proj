#include <iostream>
using namespace std;
int main() {
	cout << "Hello, World!" << endl;
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


	return 0;
}