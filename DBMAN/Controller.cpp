#include "Controller.h"
/*
 * Class Controller
 * Clase que administra toda la aplicacion
 */
Controller::Controller() {
    this->contRegisters = 0;
}

void Controller::menu() {
    char opcion = '0';
    do {
        clearScreen();
        std::cout << "Bienvenidos al Sistema Gestor de Base de Datos" << '\n';
        std::cout << "\t:::::: Menu ::::::\t" << '\n';

        std::cout << "1) Crear Base de Datos." << '\n';
        std::cout << "2) Agregar Tabla a una Base de Datos." << '\n';
        std::cout << "3) Agregar Registo a una Tabla." << '\n';

        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        do {
            if (opcion <= 48 or opcion >= 50) {
                std::cout << "Seleccione una opcion correcta: ";
                std::cin >> opcion;
            } else break;
        } while (true);
        clearScreen();
        switch (opcion) {
            case '1':
                crearBaseDeDatos();
                break;
            case '2':
                agregarTabla();
                break;
            case '3':
                agregarRegistro();
                break;
            
        }
    } while (opcion != '3');
}

/*
 * Crea una Base de Datos, luego inserta a la lista de Bases de Datos
 * input: nombre_base_de_datos
 */
void Controller::crearBaseDeDatos() {
    std::cout << "Creando una Base de Datos" << std::endl;
    std::string nombreDataBase;
    std::cout << "Nombre de la Base de Datos: ";
    std::cin >> nombreDataBase;
    this->databases.push_back(DataBase(nombreDataBase, this->contDataBases));
    this->contDataBases++;
    std::cout << "Base de Datos creada" << std::endl;
    std::cout<< "Presione enter para continuar..." << std::endl;
    std::cin.ignore();
    std::cin.ignore();
}

/*
 * Crea y Agrega una Tabla a una determinada Base de Datos, creada anteriormente
 * Si no existe Base de Datos Creada, termina la funcion
 *
 * input: id_data_base, nombre_tabla, cabeceras de las columnas
 *
 */
void Controller::agregarTabla() {
    if (this->databases.empty()) {
        std::cout << "Primero cree una Base de Datos para agregar Tablas" << std::endl;
        return;
    }
    std::cout << "Agregando Tabla a una Base de Datos" << std::endl;
    std::cout << std::endl;
    std::cout << "Bases de Datos disponibles" << std::endl;
    for (auto i = this->databases.begin(); i != this->databases.end(); i++) {
        std::cout << i->getIdDatabase() << ") " << i->getNombre() << std::endl;
    }

    int idTempDataBase;
    std::cout << "Seleccione la base de datos: ";
    std::cin >> idTempDataBase;

    auto tempDataBase = this->databases.begin();
    advance(tempDataBase, idTempDataBase);



    std::string nombreTabla;
    std::cout << "Nombre de la Tabla: ";
    std::cin >> nombreTabla;

    std::list<std::string> tempEncabezados;
    tempEncabezados.push_back("id"); // El campo id es insertado automaticamente por el
                                     // sistema
    std::string opcionSINO;

    do {
        std::cout << "Agregar Columna [SI/NO]: ";
        std::cin >> opcionSINO;
        if (opcionSINO == "SI" or opcionSINO == "si") {
            std::string nombreTemp;
            std::cout << "Nombre de la Columna: ";
            std::cin >> nombreTemp;
            tempEncabezados.push_back(nombreTemp);

        }
    } while (opcionSINO == "SI" or opcionSINO == "si");


    int idTempTable = tempDataBase->getContTables();

    // Añadimos la tabla creada a la base de datos seleccionada
    tempDataBase->addTable(Table(nombreTabla, tempEncabezados, idTempTable));

    std::cout << "Tabla agregada" << std::endl;

    std::cout<< "Presione enter para continuar..." << std::endl;
    std::cin.ignore();
    std::cin.ignore();
}

/*
 * Agrega un registro a una tabla de una base de datos.
 * verifica si hay bases de datos creada.
 * verifica si hay tablas creadas en la base de datos.
 * input: valores de los registros.
 * Cada registro se alamacena en el disco, tambien se asigna un idetificador,
 * para la indexacion.
 */
void Controller::agregarRegistro() {
    if (this->databases.empty()) {
        std::cout << "Primero cree una Base de Datos para agregar Tablas" << std::endl;
        return;
    }
    std::cout << "Agregando registro a una Tabla" << std::endl;
    std::cout << "Bases de Datos disponibles" << std::endl;
    for (auto & database : this->databases) {
        std::cout << database.getIdDatabase() << ") " << database.getNombre() << std::endl;
    }

    int idTempDataBase;
    std::cout << "Seleccione la base de datos: ";
    std::cin >> idTempDataBase;

    auto tempDataBase = this->databases.begin();
    std::advance(tempDataBase, idTempDataBase);

    if (tempDataBase->getContTables() == 0) {
        std::cout << "Agregue una tabla primero" << std::endl;
        return;
    }

    std::cout << "Tablas disponibles" << std::endl;
    for (auto & i : *tempDataBase->getTables()) {
        std::cout << i.getIdTable() << ") " << i.getNombre() << std::endl;
    }

    int idTempTable;
    std::cout << "Seleccione una Tabla: ";
    std::cin >> idTempTable;

    auto tempTable = tempDataBase->getTables()->begin();
    std::advance(tempTable, idTempTable);

    std::list<std::string> tempValoresColumnas;

    for (auto i = tempTable->getEncabezados().begin(); i != tempTable->getEncabezados().end(); i++) {
        if (i == tempTable->getEncabezados().begin()) continue;
        std::string valueTempColum;
        std::cout << *i << ": ";
        std::cin >> valueTempColum;
        tempValoresColumnas.push_back(valueTempColum);
    }

    int idTempRegister = tempTable->getIdRegister();
    
    tempValoresColumnas.push_front(std::to_string(idTempRegister));

    NodeRegister tempNodeRegister(tempValoresColumnas, this->contRegisters);


    /* 
     * El registro creado, se añade al disco,
     * y la direccion del registro en disco
     * se almacena en la estructura(B+Tree)
     * para su posterior manipulacion
     */
    // Add disk
    this->totalRegisters.push_back(tempNodeRegister);

    tempTable->addRegister(contRegisters);

    this->contRegisters++;
    std::cout << "Correcto Registro" << std::endl;
    std::cout<< "Presione enter para continuar..." << std::endl;
    std::cin.ignore();
    std::cin.ignore();
}
