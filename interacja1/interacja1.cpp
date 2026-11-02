#include <iostream>

using namespace std;

// Krok 2: Wyświetlanie aktualnego stanu populacji
void showPopulation(int day, int susceptible, int infected, int recovered) {
    cout << "\n-----------------------------\n";
    cout << "Day: " << day << "\n";
    cout << "Susceptible: " << susceptible << "\n";
    cout << "Infected: " << infected << "\n";
    cout << "Recovered: " << recovered << "\n";
    cout << "Total: " << (susceptible + infected + recovered) << "\n";
    cout << "-----------------------------\n";
}

// Krok 5: Weryfikacja spójności modelu
bool checkPopulation(int susceptible, int infected, int recovered) {
    if (susceptible < 0 || infected < 0 || recovered < 0) {
        cout << "[ERROR] Liczebnosc zadnej z grup nie moze byc ujemna!\n";
        return false;
    }
    if (susceptible + infected + recovered != 100) {
        cout << "[ERROR] Suma populacji wynosi "
            << (susceptible + infected + recovered)
            << ", a powinna dokladnie 100!\n";
        return false;
    }
    return true;
}

// Krok 4: Symulacja pojedynczego dnia
void simulateDay(int& day, int& susceptible, int& infected, int& recovered,
    double infectionRate, double recoveryRate) {
    // 1. Zapamiętanie liczebności grup na początku dnia
    int initInfected = infected;
    int initSusceptible = susceptible;

    // 2. Obliczenie nowych przypadków (rzutowanie na int zaokrągla w dół dla liczb dodatnich)
    int newInfections = (int)(initInfected * infectionRate);
    int newRecoveries = (int)(initInfected * recoveryRate);

    // 3. Ograniczenie do dostępnej liczby osób (zamiast std::min)
    if (newInfections > initSusceptible) {
        newInfections = initSusceptible;
    }
    if (newRecoveries > initInfected) {
        newRecoveries = initInfected;
    }

    // 4. Aktualizacja stanu populacji
    susceptible = initSusceptible - newInfections;
    infected = initInfected + newInfections - newRecoveries;
    recovered = recovered + newRecoveries;

    // 5. Zwiększenie licznika dni
    day++;
}

int main() {
    // Krok 1: Inicjalizacja stanu początkowego oraz parametrów
    int susceptible = 80;
    int infected = 10;
    int recovered = 10;
    int day = 0;

    double infectionRate = 0.20;
    double recoveryRate = 0.10;

    bool running = true;

    // Krok 6: Główna pętla programu
    while (running) {
        // Zawsze pokazujemy stan przed menu
        showPopulation(day, susceptible, infected, recovered);

        // Krok 3: Wyświetlenie menu
        cout << "=== Epidemic Simulator ===\n";
        cout << "1. Simulate next day\n";
        cout << "2. Change model parameters\n";
        cout << "3. Exit\n";
        cout << "Your choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            simulateDay(day, susceptible, infected, recovered, infectionRate, recoveryRate);

            // Sprawdzenie poprawności po symulacji
            if (!checkPopulation(susceptible, infected, recovered)) {
                cout << "Symulacja zostala przerwana z powodu bledu spojnosci danych.\n";
                running = false;
            }
            break;
        }
        case 2: {
            // Krok 7: Zmiana parametrów z walidacją
            double tempInfectionRate, tempRecoveryRate;

            cout << "Enter infection rate (0-1): ";
            cin >> tempInfectionRate;
            cout << "Enter recovery rate (0-1): ";
            cin >> tempRecoveryRate;

            bool validInfection = (tempInfectionRate >= 0.0 && tempInfectionRate <= 1.0);
            bool validRecovery = (tempRecoveryRate >= 0.0 && tempRecoveryRate <= 1.0);

            if (validInfection && validRecovery) {
                infectionRate = tempInfectionRate;
                recoveryRate = tempRecoveryRate;
                cout << "Parameters updated.\n";
            }
            else {
                cout << "Error: Values must be in range [0, 1]. Parameters were not changed.\n";
            }
            break;
        }
        case 3:
            cout << "Exiting simulator. Goodbye!\n";
            running = false;
            break;

        default:
            cout << "Invalid choice! Please choose an option from 1 to 3.\n";
            break;
        }
    }

    return 0;
}