#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

const int MAX_MOVIES = 6000;
const int MAX_CLIE=2000;
struct Movie     //Corresponde a la estuctura de datos de Peliculas
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

struct Customer  //Corresponde a la estuctura de datos de Customer
{
    string name;
    string rentedMovie;
};

struct Cliente     //Corresponde a la estuctura de datos de Peliculas
{
    int id;
    string nombre;
    string cedula;
    string telefono;
};
/*string getCurrentDate()
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);
    stringstream dateStream;
    dateStream << setw(2) << setfill('0') << now->tm_mday << "/"
               << setw(2) << setfill('0') << now->tm_mon + 1 << "/"
               << now->tm_year + 1900;
    return dateStream.str();
}*/

void printMovie(const Movie &movie)
{

    cout << "\n=========================================" << endl;
    cout << "\nID: " << movie.id << endl;
    cout << "Titulo: " << movie.title << endl;
    cout << "Genero: " << movie.genres << endl;
    cout << "Duracion: " << movie.duration << " minutos" << endl;
    cout << "Director: " << movie.director << endl;
    cout << "Fecha de lanzamiento: " << movie.releaseDate << endl;
    cout << "Rentado por: " << movie.rentTo << endl;
    cout << "Dia rentado:" << movie.rentDate << endl;
    cout << "Status: " << movie.status << endl
         << endl;
    cout << "=========================================" << endl;
}

void displayMovies(const Movie movies[], int size)
{
    cout << "\nMostrar Peliculas:\n"
         << endl;
    cout << "1. Mostrar todas las peliculas: " << endl;
    cout << "2. Filtro de las peliculas" << endl;

    int displayChoice;
    cout << "Ingrese su opcion de visualizacion: ";
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
        cout << "Todas las peliculas:" << endl;
        if (size == 0)
        {
            cout << "No se encontraron peliculas." << endl;
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
        cout << "Filtro de la pelicula: "
             << endl;
        cout << "1. Filtro por genero" << endl;
        cout << "2. Filtro por duracion" << endl;
        cout << "3. Filtro por director" << endl;
        cout << "4. Filtro por fecha de lanzamiento" << endl;
        cout << "5. Filtro por ID" << endl;

        int filterChoice;
        cout << "Ingrese su opcion de filtro: ";
        cin >> filterChoice;

        switch (filterChoice)
        {
        case 1:
            cout << "Ingrese el genero: ";
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
                cout << "No se encontraron peliculas de ese genero." << endl;
            }
            break;
        case 2:
            cout << "Ingrese duracion exacta (minutos): ";
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
                cout << "No se encontraron peliculas con esa duracion." << endl;
            }
            break;
        case 3:
            cout << "Ingrese el director de la pelicula: ";
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
                cout << "No se encontraron peliculas de ese director." << endl;
            }
            break;
        case 4:
            cout << "Ingrese la fecha de lanzamiento de la pelicula (yyyy-mm-dd): ";
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
                cout << "No se encontraron peliculas con esa fecha de lanzamiento." << endl;
            }
            break;
        case 5:
            cout << "Ingrese el ID de la pelicula: ";
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
                cout << "No se encontraron peliculas con ese ID." << endl;
            }
            break;
        default:
            cout << "Filtro invalido." << endl;
        }
        break;
    default:
        cout << "Eleccion de visualizacion no valida." << endl;
    }
}

void loadMovies(Movie movies[], int &size)
{
    ifstream file("movies.csv");
    if (!file.is_open())
    {
        cout << "No se pudo abrir el archivo movies.csv. Creando una nueva carpeta" << endl;
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
            
            size_t startQuotePos = line.find("\"");
            size_t endQuotePos = line.find("\"", startQuotePos + 1);

            if (endQuotePos != string::npos)
            {
                
                movies[size].title = line.substr(startQuotePos + 1, endQuotePos - startQuotePos - 1);

                
                string restOfLine;
                getline(iss >> std::ws, restOfLine);

                
                istringstream restIss(restOfLine);

                
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
            
            getline(iss, movies[size].title, ',');
            
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


void saveMovies(const Movie movies[], int size)
{
    ofstream file("movies.csv");
    if (!file.is_open())
    {
        cout << "no se pudo abrir movies.csv para escribir" << endl;
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


void saveCustomer(const Customer &customer)
{
    ofstream customersFile("customers.dat", ios::binary | ios::app);
    if (customersFile.is_open())
    {
        customersFile.write(reinterpret_cast<const char *>(&customer), sizeof(Customer));
        customersFile.close();
        cout << "La informacion del cliente se guardo correctamente." << endl;
    }
    else
    {
        cout << "No se pueden abrir costumer. data para escribir" << endl;
    }
}

void searchCustomer(const string &customerName)
{
    ifstream customersFile("customers.dat", ios::binary);
    if (!customersFile.is_open())
    {
        cout << "No se pudo abrir customers.dat. creando un nuevo archivo." << endl;
        ofstream newFile("customers.dat", ios::binary);
        newFile.close();
        return;
    }

    Customer customer;
    bool found = false;
    while (customersFile.read(reinterpret_cast<char *>(&customer), sizeof(Customer)))
    {

        cout << "Nombre: " << customer.name << endl;
        cout << "Pelicula rentada: " << customer.rentedMovie << endl;

        string lowercaseCustomerName = customer.name;
        transform(lowercaseCustomerName.begin(), lowercaseCustomerName.end(), lowercaseCustomerName.begin(), ::tolower);

        string lowercaseInputName = customerName;
        transform(lowercaseInputName.begin(), lowercaseInputName.end(), lowercaseInputName.begin(), ::tolower);

        if (lowercaseCustomerName == lowercaseInputName)
        {
            cout << "Cliente encontrado:\n"
                 << endl;
            cout << "Nombre: " << customer.name << endl;
            cout << "Pelicula rentada: " << customer.rentedMovie << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Cliente no encontrado." << endl;
    }

    customersFile.close();
}


int main()
{
   
    Movie movies[MAX_MOVIES];
    int movieSize = 0;
    
    
    Cliente array[MAX_CLIE];
    int indice=0;
    
    loadMovies(movies, movieSize);

    while (true)
    {
      
        cout << "\nTuPelicula System\n"<< endl;
        cout << "1. Mostrar Peliculas" << endl;
        cout << "2. Consultar Estado de Alquiler" << endl;
        cout << "3. Rentar Pelicula" << endl;
        cout << "4. Anadir Nueva Pelicula" << endl;
        cout << "5. Crear Cliente"<< endl;
        cout << "6. Buscar Cliente" << endl;
        cout << "7. Borrar Cliente"<<endl;
        cout << "8. Peliculas Disponibles"<<endl;
        cout << "9. Borrar Peliculas"<<endl;
        cout << "10. Salir" << endl;

        int choice;
        cout << "Ingrese su eleccion: ";
        cin >> choice;

       
        switch (choice)
        {
        case 1:
            displayMovies(movies, movieSize);
            break;
        case 2:
        {
            cout << "Consultar estado de alquiler:\n"
                 << endl;
            cout << "Ingrese ID de pelicula: ";
            int movieID;
            cin >> movieID;

            bool movieFound = false;
            bool foundRentedMovies = false;

            for (int i = 0; i < movieSize; ++i)
            {
                if (movies[i].id == movieID)
                {
                    cout << "Estado de renta: " << movies[i].status << endl;
                    if (movies[i].status == "Rentado")
                    {
                        cout << "Rentado a: " << movies[i].rentTo << endl;
                        //cout << "Rentado en: " << movies[i].rentDate << endl;
                        foundRentedMovies = true;
                    }
                    movieFound = true;
                    break;
                }
            }

            if (!movieFound)
            {
                cout << "Pelicula no encontrada." << endl;
            }
            else if (!foundRentedMovies)
            {
                cout << "Pelicula no rentada." << endl;
            }
        }
        break;
        case 3: 
            {
                int movieID;
                cout << "Ingrese ID de pelicula: ";
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
                    if (movies[movieIndex].status == "Available" || movies[movieIndex].status == "")
                    {
                        //Aca se debe ingresar el nombre del cliente a que se le renta la pelicula.
                        cout << "Ingrese nombre del cliente: ";
                        string customerName;
                        cin.ignore();
                        getline(cin, customerName);

                       
                        movies[movieIndex].rentTo = customerName;
                        //movies[movieIndex].rentDate = getCurrentDate();
                        movies[movieIndex].status = "Rentado";

                        Customer customer;
                        customer.name = customerName;
                        customer.rentedMovie = movies[movieIndex].title;
                        saveCustomer(customer);

                        cout << "Pelicua rentada exitosamente." << endl;
                    }
                    else
                    {
                        cout << "Pelicula ya rentada." << endl;
                    }
                }
                else
                {
                    cout << "Pelicula no encontrada." << endl;
                }
            }
            break;
        case 4:
            {
                cout << "Introduce el nombre de la pelicula: ";
                cin.ignore();
                getline(cin, movies[movieSize].title);

                cout << "Ingrese el genero de la pelicula: ";
                getline(cin, movies[movieSize].genres);

                cout << "Ingrese la duracion de la pelicula (minutos): ";
                cin >> movies[movieSize].duration;

                cout << "Ingrese el director de la pelicula: ";
                cin.ignore();
                getline(cin, movies[movieSize].director);

                cout << "Ingrese la fecha de estreno de la pelicula (dd/mm/yyyy): ";
                cin >> movies[movieSize].releaseDate;

                movies[movieSize].id = movieSize + 1;
                movies[movieSize].rentTo = "";
                movies[movieSize].rentDate = "";
                movies[movieSize].status = "Available";

                ++movieSize;
            }
            break;
        case 5:
           /*{
               string customerName;
                cout << "\nIngresa el nombre: ";
                cin.ignore();
                getline(cin, customerName);
                searchCustomer(customerName);
            }*/
            {
                cout << "Nombre de Cliente: ";
                cin.ignore();
                getline(cin, array[indice].nombre);

                cout << "Cedula de Cliente: ";
                getline(cin, array[indice].cedula);

                cout << "Telefono de Cliente";
                cin >> array[indice].telefono;


                array[indice].id = indice + 1;

                ++indice;
            }
            break;
        case 6:
            
        break;
        case 9:
            saveMovies(movies, movieSize);
            cout << "Saliendo de TuPelicula System. Adios!" << endl;
            return 0;
        default:
            cout << "Eleccion invalida. Por favor vuelva a intentarlo." << endl;
        }
    }

    return 0;
}
