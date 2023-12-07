
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

const int MAX_MOVIES = 6000;

struct Movie
{
    int id;
    string title;
    string genres;
    int duration;
    string director;
    string releaseDate;
    string rentTo;
    string rentDate;
    string status;
};

struct Customer
{
    string name;
    string rentedMovie;
};
struct Cliente{
  int id;
  string nombre;
  string cedula;
  string telefono;    
};


// Imprime Pelicula
void printMovie(const Movie &movie)
{

    cout << "\n=========================================" << endl;
    cout << "\nID: " << movie.id << endl;
    cout << "Titulo: " << movie.title << endl;
    cout << "Genero: " << movie.genres << endl;
    cout << "Duracion: " << movie.duration << " minutos" << endl;
    cout << "Director: " << movie.director << endl;
    cout << "Fecha Lanzamiento: " << movie.releaseDate << endl;
    cout << "Rentado a: " << movie.rentTo << endl;
    cout << "Fecha Renta: " << movie.rentDate << endl;
    cout << "Status: " << movie.status << endl
         << endl;
    cout << "=========================================" << endl;
}

// Permite mostrar peliculas todas y por filtro de genero, id, fecha lanzamiento, director, nombre
void displayMovies(const Movie movies[], int size)
{
    cout << "\nMostrar Pelicular:\n"
         << endl;
    cout << "1. Mostrar todas las peliculas" << endl;
    cout << "2. Filtro de Pelicula" << endl;

    int displayChoice;
    cout << "\nIngresa una opcion: ";
    cin >> displayChoice;

    // Variables de filtro
    string filter;
    string genreFilter;
    int durationFilter;
    string directorFilter;
    string releaseDateFilter;
    int idFilter;

    bool foundGenre = false;
    bool foundDuration = false;
    bool foundDirector = false;
    bool foundReleaseDate = false;
    bool foundID = false;

    switch (displayChoice)
    {
    case 1:
        cout << "\nTodas las Peliculas:" << endl;
        if (size == 0)
        {
            cout << "\nNo hay Pelicuals." << endl;
        }
        else
        {
            for (int i = 0; i < size; ++i)
            {
                printMovie(movies[i]);
            }
        }
        break;
    case 2:
        cout << "\nFiltro de Pelicualas:\n"
             << endl;
        cout << "1. Buscar por Genero" << endl;
        cout << "2. Buscar por Duracion" << endl;
        cout << "3. Buscar por Director" << endl;
        cout << "4. Buscar por fecha de lanzamiento" << endl;
        cout << "5. Buscar por ID" << endl;

        int filterChoice;
        cout << "\nIngrese una opcion: ";
        cin >> filterChoice;

        switch (filterChoice)
        {
        case 1:
            cout << "\nIngrese genero: ";
            cin.ignore();
            getline(cin, genreFilter);
            transform(genreFilter.begin(), genreFilter.end(), genreFilter.begin(), ::tolower);

            foundGenre = false;
            for (int i = 0; i < size; ++i)
            {
                string lowerGenres = movies[i].genres;
                transform(lowerGenres.begin(), lowerGenres.end(), lowerGenres.begin(), ::tolower);

                if (lowerGenres.find(genreFilter) != string::npos)
                {
                    printMovie(movies[i]);
                    foundGenre = true;
                }
            }

            if (!foundGenre)
            {
                cout << "\nNo hay peliculas por el genero ingresado." << endl;
            }
            break;
        case 2:
            cout << "\nIngresa duracion exacta en minutos: ";
            cin >> durationFilter;

            foundDuration = false;
            for (int i = 0; i < size; ++i)
            {
                if (movies[i].duration == durationFilter)
                {
                    printMovie(movies[i]);
                    foundDuration = true;
                }
            }

            if (!foundDuration)
            {
                cout << "\nNo hay peliculas por el tiempo de duracion ingresado." << endl;
            }
            break;
        case 3:
            cout << "\nIngresa Director: ";
            cin.ignore();
            getline(cin, directorFilter);
            transform(directorFilter.begin(), directorFilter.end(), directorFilter.begin(), ::tolower);

            foundDirector = false;
            for (int i = 0; i < size; ++i)
            {
                string lowerDirector = movies[i].director;
                transform(lowerDirector.begin(), lowerDirector.end(), lowerDirector.begin(), ::tolower);

                if (lowerDirector.find(directorFilter) != string::npos)
                {
                    printMovie(movies[i]);
                    foundDirector = true;
                }
            }

            if (!foundDirector)
            {
                cout << "\nNo hay peliculas por director ingresado." << endl;
            }
            break;
        case 4:
            cout << "\nIngrese fecha de lanzamiento (dd-mm-yyyy): ";
            cin >> releaseDateFilter;

            foundReleaseDate = false;
            for (int i = 0; i < size; ++i)
            {
                if (movies[i].releaseDate == releaseDateFilter)
                {
                    printMovie(movies[i]);
                    foundReleaseDate = true;
                }
            }

            if (!foundReleaseDate)
            {
                cout << "\nNo hay peliculas por la fecha de lanzamiento ingresada." << endl;
            }
            break;
        case 5:
            cout << "\nIngrese Id de pelicula: ";
            cin >> idFilter;

            foundID = false;
            for (int i = 0; i < size; ++i)
            {
                if (movies[i].id == idFilter)
                {
                    printMovie(movies[i]);
                    foundID = true;
                }
            }

            if (!foundID)
            {
                cout << "\nNo hay peliculas por id ingresado." << endl;
            }
            break;
        default:
            cout << "Filtro de Busqueda invalido." << endl;
        }
        break;
    default:
        cout << "Opcion invalida." << endl;
    }
}

// Funcion para cargar datos en el archivo de peliculas
void loadMovies(Movie movies[], int &size)
{
    ifstream file("movies.csv");
    if (!file.is_open())
    {
        cout << "\nWarning: Unable to open movies.csv. Creating a new file." << endl;
        ofstream newFile("movies.csv");
        newFile.close();
        return;
    }

    string line;
    while (getline(file, line) && size < MAX_MOVIES)
    {
        istringstream iss(line);
        char comma;
        iss >> movies[size].id >> comma;

        if (line.find("\"") != string::npos)
        {
            // Encontrar la posici贸n de las comillas de cierre
            size_t startQuotePos = line.find("\"");
            size_t endQuotePos = line.find("\"", startQuotePos + 1);

            if (endQuotePos != string::npos)
            {
                // Leer el t铆tulo entre las comillas
                movies[size].title = line.substr(startQuotePos + 1, endQuotePos - startQuotePos - 1);

                // Utilizar una variable separada para leer el resto de los campos despu茅s de las comillas
                string restOfLine;
                getline(iss >> std::ws, restOfLine);

                // Utilizar otra istringstream para procesar el resto de la l铆nea
                istringstream restIss(restOfLine);

                // Leer los campos restantes
                restIss >> comma; // Consumir la coma despu茅s de las comillas
                getline(restIss >> std::ws, movies[size].genres, ',');
                restIss >> movies[size].duration >> comma;
                getline(restIss >> std::ws, movies[size].director, ',');
                getline(restIss >> std::ws, movies[size].releaseDate, ',');
                getline(restIss >> std::ws, movies[size].rentTo, ',');
                getline(restIss >> std::ws, movies[size].rentDate, ',');
                getline(restIss >> std::ws, movies[size].status);
            }
        }
        else
        {
            // Si no hay comillas, leer el t铆tulo hasta la coma
            getline(iss, movies[size].title, ',');
            // Resto de los campos
            getline(iss >> std::ws, movies[size].genres, ',');
            iss >> movies[size].duration >> comma;
            getline(iss >> std::ws, movies[size].director, ',');
            getline(iss >> std::ws, movies[size].releaseDate, ',');
            getline(iss >> std::ws, movies[size].rentTo, ',');
            getline(iss >> std::ws, movies[size].rentDate, ',');
            getline(iss >> std::ws, movies[size].status);
        }

        ++size;
    }

    file.close();
}

// Funcion para guardar datos en el archivo pelicula
void saveMovies(const Movie movies[], int size)
{
    ofstream file("movies.csv");
    if (!file.is_open())
    {
        cout << "\nNo se encuentra el archivo. Creando una nueva carpeta" << endl;
        return;
    }

    for (int i = 0; i < size; ++i)
    {
        file << movies[i].id << "," << movies[i].title << "," << movies[i].genres << ","
             << movies[i].duration << "," << movies[i].director << "," << movies[i].releaseDate << ","
             << movies[i].rentTo << "," << movies[i].rentDate << "," << movies[i].status << endl;
    }

    file.close();
}

// Funci贸n para guardar informaci贸n del cliente en un archivo binario
void saveCustomer(const Customer &customer)
{
    ofstream customersFile("customers.dat", ios::binary | ios::app);
    if (customersFile.is_open())
    {
        customersFile.write(reinterpret_cast<const char *>(&customer), sizeof(Customer));
        customersFile.close();
        cout << "\nCustomer information saved successfully." << endl;
    }
    else
    {
        cout << "\nError: Unable to open customers.dat for writing" << endl;
    }
}

// Funci贸n para buscar informaci贸n de un cliente en un archivo binario
void searchCustomer(const string &customerName)
{
    ifstream customersFile("customers.dat", ios::binary);
    if (!customersFile.is_open())
    {
        cout << "\nWarning: Unable to open customers.dat. Creating a new file." << endl;
        ofstream newFile("customers.dat", ios::binary);
        newFile.close();
        return;
    }

    Customer customer;
    bool found = false;
    while (customersFile.read(reinterpret_cast<char *>(&customer), sizeof(Customer)))
    {

        cout << "\nName: " << customer.name << endl;
        cout << "\nRented Movie: " << customer.rentedMovie << endl;

        string lowercaseCustomerName = customer.name;
        transform(lowercaseCustomerName.begin(), lowercaseCustomerName.end(), lowercaseCustomerName.begin(), ::tolower);

        string lowercaseInputName = customerName;
        transform(lowercaseInputName.begin(), lowercaseInputName.end(), lowercaseInputName.begin(), ::tolower);

        if (lowercaseCustomerName == lowercaseInputName)
        {
            cout << "\nCustomer found:\n"
                 << endl;
            cout << "Name: " << customer.name << endl;
            cout << "Rented Movie: " << customer.rentedMovie << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "\nCustomer not found." << endl;
    }

    customersFile.close();
}
//Cargar cliente
void loadClientes(Cliente clientes[], int &size)
{
    ifstream file("clientes.txt");
    if (!file.is_open())
    {
        cout << "\nCreando un nuevo archivo" << endl;
        ofstream newFile("clientes.txt");
        newFile.close();
        return;
    }
}

void saveClientes(Cliente clientes[], int size)
{
    ofstream clientefile("clientes.txt");
    if (!clientefile.is_open())
    {
        cout << "\nNo se encuentra el archivo. Creando una nueva carpeta" << endl;
        return;
    }

    for (int i = 0; i < size; ++i)
    {
        clientefile << clientes[i].id << "," << clientes[i].nombre << "," << clientes[i].cedula << ","
              << clientes[i].telefono<< endl;
        cout<<"Cargado satisfactoriamente";
    }

    clientefile.close();
}
// Funci贸n principal
int main()
{
    // Arreglo de tipo pelicula y tama駉
    Movie movies[MAX_MOVIES];
    int movieSize = 0;
    // Arreglo de tipo Clientes y tama駉
    Cliente clientes[MAX_MOVIES];
    int clienteSize = 0;
    //Cargar datos desde el archivo movies.csv
    loadMovies(movies, movieSize);
    loadClientes(clientes, clienteSize);
    // Bucle principal del programa
    while (true)
    {
        // Menu Principal
        cout << "\nTu Pelicula System\n"
             << endl;
        cout << "1. Mostrar Pelicula" << endl;
        cout << "2. Consultar Estado de Alquiles" << endl;
        cout << "3. Rentar Pelicula" << endl;
        cout << "4. Agregar Pelicula Nueva" << endl;
        cout << "5. Buscar Cliente" << endl;
        cout << "6. Agregar Cliente" << endl;
        cout << "7. Salir" << endl;
        int choice;
        cout << "\nEnter para salir: ";
        cin >> choice;

        // opciones del meni
        switch (choice)
        {
        case 1:
            displayMovies(movies, movieSize);
            break;
        case 2:
        {
            cout << "\nConsultar Peliculas:\n"
                 << endl;
            cout << "Ingrese ID: ";
            int movieID;
            cin >> movieID;

            bool movieFound = false;
            bool foundRentedMovies = false;

            for (int i = 0; i < movieSize; ++i)
            {
                if (movies[i].id == movieID)
                {
                    cout << "\nStatus de Renta: " << movies[i].status << endl;
                    if (movies[i].status == "Rentado")
                    {
                        cout << "\nRentado a: " << movies[i].rentTo << endl;
                        cout << "\nFecha de Renta: " << movies[i].rentDate << endl;
                        foundRentedMovies = true;
                    }
                    movieFound = true;
                    break;
                }
            }

            if (!movieFound)
            {
                cout << "\nPelicula no encntrada." << endl;
            }
            else if (!foundRentedMovies)
            {
                cout << "\nPElicula no rentada." << endl;
            }
        }
        break;
        case 3:
            {
                int movieID;
                cout << "\nIngrese ID pelicula: ";
                cin >> movieID;

                int movieIndex = -1;
                for (int i = 0; i < movieSize; ++i)
                {
                    if (movies[i].id == movieID)
                    {
                        movieIndex = i;
                        break;
                    }
                }

                if (movieIndex != -1)
                {
                    if (movies[movieIndex].status == "Disponible" || movies[movieIndex].status == "")
                    {
                        cout << "\nIngrese Nombre: ";
                        string customerName;
                        cin.ignore();
                        getline(cin, customerName);
                        cout << "\nIngrese Fecha de Renta (dd-mm-yyyy): ";
                        string fecha;
                        cin.ignore();
                        getline(cin, fecha);
                        movies[movieIndex].rentTo = customerName;
                        movies[movieIndex].rentDate = fecha;
                        movies[movieIndex].status = "Rentado";

                        Customer customer;
                        customer.name = customerName;
                        customer.rentedMovie = movies[movieIndex].title;
                        saveCustomer(customer);

                        cout << "\nPelicula rentada exitosamente." << endl;
                    }
                    else
                    {
                        cout << "\nMovie fue rentada." << endl;
                    }
                }
                else
                {
                    cout << "\nMovie no encontrada." << endl;
                }
            }
            break;
        case 4:
            {
                cout << "\nIngresa Titulo: ";
                cin.ignore();
                getline(cin, movies[movieSize].title);

                cout << "\nIngresa Genero: ";
                getline(cin, movies[movieSize].genres);

                cout << "\nIngresa Duracion (minutes): ";
                cin >> movies[movieSize].duration;

                cout << "\nIngresa Director: ";
                cin.ignore();
                getline(cin, movies[movieSize].director);

                cout << "\nIngresa Fecha de Lanzamiento (dd/mm/yyyy): ";
                cin >> movies[movieSize].releaseDate;

                movies[movieSize].id = movieSize + 1;
                movies[movieSize].rentTo = "";
                movies[movieSize].rentDate = "";
                movies[movieSize].status = "Disponible";

                ++movieSize;
            }
            break;
        case 5:
            {
                string customerName;
                cout << "\nIngresa Nombre: ";
                cin.ignore();
                getline(cin, customerName);
                searchCustomer(customerName);
            }
            break;
            case 6:
            {
                cout << "Ingresa nombre: ";
                cin.ignore();
                getline(cin, clientes[clienteSize].nombre);

                cout << "Ingresa Cedula: ";
                getline(cin, clientes[clienteSize].cedula);

                cout << "Ingresa telefono: ";
                cin >> clientes[clienteSize].telefono;
                 saveClientes(clientes,clienteSize);
                clientes[clienteSize].id = clienteSize + 1;
                clientes[clienteSize].nombre = "";
                clientes[clienteSize].cedula = "";
                clientes[clienteSize].telefono = " ";

                ++clienteSize;
            }
            break;
        case 7:
            saveMovies(movies, movieSize);
            cout << "\nSaliendo de TuPelicula System. Adios!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
