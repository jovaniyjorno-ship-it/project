#include "pch.h"
#include "App.h"



int main() {
	try {
		App app;
		app.run();
	}
	catch (const exception &ex) {
		cout << "Ошибка: " << ex.what() << "\n";
		return 1;
	}

	return 0;
}
