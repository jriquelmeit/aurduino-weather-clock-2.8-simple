#include "santoral.h"
#include <avr/pgmspace.h>

// Mes 1
static const char s_1_1[] PROGMEM = "Sta. Maria M. de Dios";
static const char s_1_2[] PROGMEM = "S. Basilio y S. Gregorio";
static const char s_1_3[] PROGMEM = "Sto. Nombre de Jesus";
static const char s_1_4[] PROGMEM = "Sta. Angela de Foligno";
static const char s_1_5[] PROGMEM = "S. Telesforo";
static const char s_1_6[] PROGMEM = "Epifania del Senor";
static const char s_1_7[] PROGMEM = "S. Raimundo Penafort";
static const char s_1_8[] PROGMEM = "S. Severino";
static const char s_1_9[] PROGMEM = "S. Eulogio";
static const char s_1_10[] PROGMEM = "S. Guillermo";
static const char s_1_11[] PROGMEM = "S. Higinio";
static const char s_1_12[] PROGMEM = "Sta. Tatiana";
static const char s_1_13[] PROGMEM = "S. Hilario";
static const char s_1_14[] PROGMEM = "S. Felix de Nola";
static const char s_1_15[] PROGMEM = "S. Pablo Ermitano";
static const char s_1_16[] PROGMEM = "S. Marcelo";
static const char s_1_17[] PROGMEM = "S. Antonio Abad";
static const char s_1_18[] PROGMEM = "Sta. Prisca";
static const char s_1_19[] PROGMEM = "S. Mario y Sta. Marta";
static const char s_1_20[] PROGMEM = "S. Sebastian y Fabian";
static const char s_1_21[] PROGMEM = "Sta. Ines";
static const char s_1_22[] PROGMEM = "S. Vicente Martir";
static const char s_1_23[] PROGMEM = "S. Ildefonso";
static const char s_1_24[] PROGMEM = "S. Francisco de Sales";
static const char s_1_25[] PROGMEM = "Conversion S. Pablo";
static const char s_1_26[] PROGMEM = "S. Timoteo y S. Tito";
static const char s_1_27[] PROGMEM = "Sta. Angela Merici";
static const char s_1_28[] PROGMEM = "Sto. Tomas de Aquino";
static const char s_1_29[] PROGMEM = "S. Valero";
static const char s_1_30[] PROGMEM = "Sta. Martina";
static const char s_1_31[] PROGMEM = "S. Juan Bosco";
static const char* const month_1[] PROGMEM = {
    s_1_1,
    s_1_2,
    s_1_3,
    s_1_4,
    s_1_5,
    s_1_6,
    s_1_7,
    s_1_8,
    s_1_9,
    s_1_10,
    s_1_11,
    s_1_12,
    s_1_13,
    s_1_14,
    s_1_15,
    s_1_16,
    s_1_17,
    s_1_18,
    s_1_19,
    s_1_20,
    s_1_21,
    s_1_22,
    s_1_23,
    s_1_24,
    s_1_25,
    s_1_26,
    s_1_27,
    s_1_28,
    s_1_29,
    s_1_30,
    s_1_31,
};

// Mes 2
static const char s_2_1[] PROGMEM = "Sta. Brigida";
static const char s_2_2[] PROGMEM = "Ntra. Sra. Candelaria";
static const char s_2_3[] PROGMEM = "S. Blas";
static const char s_2_4[] PROGMEM = "S. Gilberto";
static const char s_2_5[] PROGMEM = "Sta. Agueda";
static const char s_2_6[] PROGMEM = "S. Pablo Miki";
static const char s_2_7[] PROGMEM = "S. Ricardo";
static const char s_2_8[] PROGMEM = "S. Jeronimo Emiliani";
static const char s_2_9[] PROGMEM = "Sta. Apolonia";
static const char s_2_10[] PROGMEM = "Sta. Escolastica";
static const char s_2_11[] PROGMEM = "Ntra. Sra. de Lourdes";
static const char s_2_12[] PROGMEM = "Sta. Eulalia";
static const char s_2_13[] PROGMEM = "S. Benigno";
static const char s_2_14[] PROGMEM = "S. Valentin";
static const char s_2_15[] PROGMEM = "S. Faustino";
static const char s_2_16[] PROGMEM = "Sta. Juliana";
static const char s_2_17[] PROGMEM = "Siete Santos Fund.";
static const char s_2_18[] PROGMEM = "S. Eladio";
static const char s_2_19[] PROGMEM = "S. Alvaro de Cordoba";
static const char s_2_20[] PROGMEM = "S. Eleuterio";
static const char s_2_21[] PROGMEM = "S. Pedro Damian";
static const char s_2_22[] PROGMEM = "Catedra de S. Pedro";
static const char s_2_23[] PROGMEM = "S. Policarpo";
static const char s_2_24[] PROGMEM = "S. Matias Apostol";
static const char s_2_25[] PROGMEM = "S. Cesario";
static const char s_2_26[] PROGMEM = "S. Nestor";
static const char s_2_27[] PROGMEM = "S. Gabriel Dolorosa";
static const char s_2_28[] PROGMEM = "S. Roman";
static const char s_2_29[] PROGMEM = "S. Augusto";
static const char* const month_2[] PROGMEM = {
    s_2_1,
    s_2_2,
    s_2_3,
    s_2_4,
    s_2_5,
    s_2_6,
    s_2_7,
    s_2_8,
    s_2_9,
    s_2_10,
    s_2_11,
    s_2_12,
    s_2_13,
    s_2_14,
    s_2_15,
    s_2_16,
    s_2_17,
    s_2_18,
    s_2_19,
    s_2_20,
    s_2_21,
    s_2_22,
    s_2_23,
    s_2_24,
    s_2_25,
    s_2_26,
    s_2_27,
    s_2_28,
    s_2_29,
};

// Mes 3
static const char s_3_1[] PROGMEM = "S. Rosendo";
static const char s_3_2[] PROGMEM = "S. Simplicio";
static const char s_3_3[] PROGMEM = "S. Emeterio y Celedonio";
static const char s_3_4[] PROGMEM = "S. Casimiro";
static const char s_3_5[] PROGMEM = "S. Juan Jose Cruz";
static const char s_3_6[] PROGMEM = "S. Olegario";
static const char s_3_7[] PROGMEM = "Sta. Perpetua y Felicidad";
static const char s_3_8[] PROGMEM = "S. Juan de Dios";
static const char s_3_9[] PROGMEM = "Sta. Francisca Romana";
static const char s_3_10[] PROGMEM = "S. Macario";
static const char s_3_11[] PROGMEM = "S. Eulogio Cordoba";
static const char s_3_12[] PROGMEM = "S. Maximiliano";
static const char s_3_13[] PROGMEM = "S. Rodrigo";
static const char s_3_14[] PROGMEM = "Sta. Matilde";
static const char s_3_15[] PROGMEM = "Sta. Luisa Marillac";
static const char s_3_16[] PROGMEM = "S. Heriberto";
static const char s_3_17[] PROGMEM = "S. Patricio";
static const char s_3_18[] PROGMEM = "S. Cirilo Jerusalen";
static const char s_3_19[] PROGMEM = "San Jose";
static const char s_3_20[] PROGMEM = "S. Martin de Braga";
static const char s_3_21[] PROGMEM = "S. Nicolas de Flue";
static const char s_3_22[] PROGMEM = "Sta. Lea";
static const char s_3_23[] PROGMEM = "S. Turibio Mogrovejo";
static const char s_3_24[] PROGMEM = "S. Gabriel Arcangel";
static const char s_3_25[] PROGMEM = "Anunciacion Senor";
static const char s_3_26[] PROGMEM = "S. Braulio";
static const char s_3_27[] PROGMEM = "S. Ruperto";
static const char s_3_28[] PROGMEM = "S. Sixto III";
static const char s_3_29[] PROGMEM = "S. Segundo";
static const char s_3_30[] PROGMEM = "S. Juan Climaco";
static const char s_3_31[] PROGMEM = "S. Benjamin";
static const char* const month_3[] PROGMEM = {
    s_3_1,
    s_3_2,
    s_3_3,
    s_3_4,
    s_3_5,
    s_3_6,
    s_3_7,
    s_3_8,
    s_3_9,
    s_3_10,
    s_3_11,
    s_3_12,
    s_3_13,
    s_3_14,
    s_3_15,
    s_3_16,
    s_3_17,
    s_3_18,
    s_3_19,
    s_3_20,
    s_3_21,
    s_3_22,
    s_3_23,
    s_3_24,
    s_3_25,
    s_3_26,
    s_3_27,
    s_3_28,
    s_3_29,
    s_3_30,
    s_3_31,
};

// Mes 4
static const char s_4_1[] PROGMEM = "S. Hugo";
static const char s_4_2[] PROGMEM = "S. Francisco de Paula";
static const char s_4_3[] PROGMEM = "S. Ricardo";
static const char s_4_4[] PROGMEM = "S. Isidoro de Sevilla";
static const char s_4_5[] PROGMEM = "S. Vicente Ferrer";
static const char s_4_6[] PROGMEM = "S. Celestino";
static const char s_4_7[] PROGMEM = "S. Juan B. de La Salle";
static const char s_4_8[] PROGMEM = "S. Dionisio";
static const char s_4_9[] PROGMEM = "Sta. Casilda";
static const char s_4_10[] PROGMEM = "S. Ezequiel";
static const char s_4_11[] PROGMEM = "S. Estanislao";
static const char s_4_12[] PROGMEM = "S. Julio";
static const char s_4_13[] PROGMEM = "S. Hermenegildo";
static const char s_4_14[] PROGMEM = "S. Tiburcio";
static const char s_4_15[] PROGMEM = "S. Telmo";
static const char s_4_16[] PROGMEM = "Sta. Bernardita";
static const char s_4_17[] PROGMEM = "S. Aniceto";
static const char s_4_18[] PROGMEM = "S. Perfecto";
static const char s_4_19[] PROGMEM = "S. Expedito";
static const char s_4_20[] PROGMEM = "Sta. Ines Montepulciano";
static const char s_4_21[] PROGMEM = "S. Anselmo";
static const char s_4_22[] PROGMEM = "S. Sotero y S. Cayo";
static const char s_4_23[] PROGMEM = "S. Jorge";
static const char s_4_24[] PROGMEM = "S. Fidel Sigmaringa";
static const char s_4_25[] PROGMEM = "S. Marcos Evangelista";
static const char s_4_26[] PROGMEM = "S. Isidoro";
static const char s_4_27[] PROGMEM = "Ntra. Sra. Montserrat";
static const char s_4_28[] PROGMEM = "S. Pedro Chanel";
static const char s_4_29[] PROGMEM = "Sta. Catalina de Siena";
static const char s_4_30[] PROGMEM = "S. Pio V";
static const char* const month_4[] PROGMEM = {
    s_4_1,
    s_4_2,
    s_4_3,
    s_4_4,
    s_4_5,
    s_4_6,
    s_4_7,
    s_4_8,
    s_4_9,
    s_4_10,
    s_4_11,
    s_4_12,
    s_4_13,
    s_4_14,
    s_4_15,
    s_4_16,
    s_4_17,
    s_4_18,
    s_4_19,
    s_4_20,
    s_4_21,
    s_4_22,
    s_4_23,
    s_4_24,
    s_4_25,
    s_4_26,
    s_4_27,
    s_4_28,
    s_4_29,
    s_4_30,
};

// Mes 5
static const char s_5_1[] PROGMEM = "S. Jose Obrero";
static const char s_5_2[] PROGMEM = "S. Atanasio";
static const char s_5_3[] PROGMEM = "Invencion Sta. Cruz";
static const char s_5_4[] PROGMEM = "S. Floriano";
static const char s_5_5[] PROGMEM = "S. Angel";
static const char s_5_6[] PROGMEM = "Sto. Domingo Savio";
static const char s_5_7[] PROGMEM = "Sta. Flavia";
static const char s_5_8[] PROGMEM = "Ntra. Sra. de Lujan";
static const char s_5_9[] PROGMEM = "S. Pacomio";
static const char s_5_10[] PROGMEM = "S. Juan de Avila";
static const char s_5_11[] PROGMEM = "S. Ignacio Laconi";
static const char s_5_12[] PROGMEM = "S. Pancracio";
static const char s_5_13[] PROGMEM = "Ntra. Sra. de Fatima";
static const char s_5_14[] PROGMEM = "S. Matias";
static const char s_5_15[] PROGMEM = "S. Isidro Labrador";
static const char s_5_16[] PROGMEM = "S. Juan Nepomuceno";
static const char s_5_17[] PROGMEM = "S. Pascual Bailon";
static const char s_5_18[] PROGMEM = "S. Juan I";
static const char s_5_19[] PROGMEM = "S. Celestino V";
static const char s_5_20[] PROGMEM = "S. Bernardino Siena";
static const char s_5_21[] PROGMEM = "S. Cristobal Magallanes";
static const char s_5_22[] PROGMEM = "Sta. Rita de Casia";
static const char s_5_23[] PROGMEM = "S. Juan B. Rossi";
static const char s_5_24[] PROGMEM = "Maria Auxiliadora";
static const char s_5_25[] PROGMEM = "S. Beda y Gregorio VII";
static const char s_5_26[] PROGMEM = "S. Felipe Neri";
static const char s_5_27[] PROGMEM = "S. Agustin Canterbury";
static const char s_5_28[] PROGMEM = "S. German";
static const char s_5_29[] PROGMEM = "S. Maximo";
static const char s_5_30[] PROGMEM = "S. Fernando";
static const char s_5_31[] PROGMEM = "Visitacion Virgen";
static const char* const month_5[] PROGMEM = {
    s_5_1,
    s_5_2,
    s_5_3,
    s_5_4,
    s_5_5,
    s_5_6,
    s_5_7,
    s_5_8,
    s_5_9,
    s_5_10,
    s_5_11,
    s_5_12,
    s_5_13,
    s_5_14,
    s_5_15,
    s_5_16,
    s_5_17,
    s_5_18,
    s_5_19,
    s_5_20,
    s_5_21,
    s_5_22,
    s_5_23,
    s_5_24,
    s_5_25,
    s_5_26,
    s_5_27,
    s_5_28,
    s_5_29,
    s_5_30,
    s_5_31,
};

// Mes 6
static const char s_6_1[] PROGMEM = "S. Justino";
static const char s_6_2[] PROGMEM = "S. Marcelino y S. Pedro";
static const char s_6_3[] PROGMEM = "S. Carlos Lwanga";
static const char s_6_4[] PROGMEM = "S. Quirino";
static const char s_6_5[] PROGMEM = "S. Bonifacio";
static const char s_6_6[] PROGMEM = "S. Norberto";
static const char s_6_7[] PROGMEM = "S. Roberto";
static const char s_6_8[] PROGMEM = "S. Medardo";
static const char s_6_9[] PROGMEM = "S. Efren";
static const char s_6_10[] PROGMEM = "Sta. Margarita Escocia";
static const char s_6_11[] PROGMEM = "S. Bernabe Apostol";
static const char s_6_12[] PROGMEM = "S. Onofre";
static const char s_6_13[] PROGMEM = "S. Antonio de Padua";
static const char s_6_14[] PROGMEM = "S. Eliseo";
static const char s_6_15[] PROGMEM = "S. Vito";
static const char s_6_16[] PROGMEM = "S. Aureliano";
static const char s_6_17[] PROGMEM = "S. Ismael";
static const char s_6_18[] PROGMEM = "S. Gregorio Barbarigo";
static const char s_6_19[] PROGMEM = "S. Romualdo";
static const char s_6_20[] PROGMEM = "S. Silverio";
static const char s_6_21[] PROGMEM = "S. Luis Gonzaga";
static const char s_6_22[] PROGMEM = "S. Paulino de Nola";
static const char s_6_23[] PROGMEM = "S. Jose Cafasso";
static const char s_6_24[] PROGMEM = "Natividad S. Juan B.";
static const char s_6_25[] PROGMEM = "S. Guillermo";
static const char s_6_26[] PROGMEM = "S. Josemaria Escriva";
static const char s_6_27[] PROGMEM = "S. Cirilo Alejandria";
static const char s_6_28[] PROGMEM = "S. Ireneo";
static const char s_6_29[] PROGMEM = "S. Pedro y S. Pablo";
static const char s_6_30[] PROGMEM = "Primeros Martires Roma";
static const char* const month_6[] PROGMEM = {
    s_6_1,
    s_6_2,
    s_6_3,
    s_6_4,
    s_6_5,
    s_6_6,
    s_6_7,
    s_6_8,
    s_6_9,
    s_6_10,
    s_6_11,
    s_6_12,
    s_6_13,
    s_6_14,
    s_6_15,
    s_6_16,
    s_6_17,
    s_6_18,
    s_6_19,
    s_6_20,
    s_6_21,
    s_6_22,
    s_6_23,
    s_6_24,
    s_6_25,
    s_6_26,
    s_6_27,
    s_6_28,
    s_6_29,
    s_6_30,
};

// Mes 7
static const char s_7_1[] PROGMEM = "S. Aaron";
static const char s_7_2[] PROGMEM = "S. Bernardino Realino";
static const char s_7_3[] PROGMEM = "Sto. Tomas Apostol";
static const char s_7_4[] PROGMEM = "Sta. Isabel Portugal";
static const char s_7_5[] PROGMEM = "S. Antonio M. Zaccaria";
static const char s_7_6[] PROGMEM = "Sta. Maria Goretti";
static const char s_7_7[] PROGMEM = "S. Fermin";
static const char s_7_8[] PROGMEM = "S. Eugenio";
static const char s_7_9[] PROGMEM = "Sta. Veronica Giuliani";
static const char s_7_10[] PROGMEM = "S. Cristobal";
static const char s_7_11[] PROGMEM = "S. Benito Abad";
static const char s_7_12[] PROGMEM = "S. Juan Gualberto";
static const char s_7_13[] PROGMEM = "S. Enrique";
static const char s_7_14[] PROGMEM = "S. Camilo de Lelis";
static const char s_7_15[] PROGMEM = "S. Buenaventura";
static const char s_7_16[] PROGMEM = "Ntra. Sra. del Carmen";
static const char s_7_17[] PROGMEM = "S. Alejo";
static const char s_7_18[] PROGMEM = "S. Federico";
static const char s_7_19[] PROGMEM = "Sta. Justa y Rufina";
static const char s_7_20[] PROGMEM = "S. Elias Profeta";
static const char s_7_21[] PROGMEM = "S. Lorenzo Brindisi";
static const char s_7_22[] PROGMEM = "Sta. Maria Magdalena";
static const char s_7_23[] PROGMEM = "Sta. Brigida de Suecia";
static const char s_7_24[] PROGMEM = "S. Charbel";
static const char s_7_25[] PROGMEM = "Santiago Apostol";
static const char s_7_26[] PROGMEM = "S. Joaquin y Sta. Ana";
static const char s_7_27[] PROGMEM = "S. Pantaleon";
static const char s_7_28[] PROGMEM = "S. Nazario";
static const char s_7_29[] PROGMEM = "Sta. Marta";
static const char s_7_30[] PROGMEM = "S. Pedro Crisologo";
static const char s_7_31[] PROGMEM = "S. Ignacio de Loyola";
static const char* const month_7[] PROGMEM = {
    s_7_1,
    s_7_2,
    s_7_3,
    s_7_4,
    s_7_5,
    s_7_6,
    s_7_7,
    s_7_8,
    s_7_9,
    s_7_10,
    s_7_11,
    s_7_12,
    s_7_13,
    s_7_14,
    s_7_15,
    s_7_16,
    s_7_17,
    s_7_18,
    s_7_19,
    s_7_20,
    s_7_21,
    s_7_22,
    s_7_23,
    s_7_24,
    s_7_25,
    s_7_26,
    s_7_27,
    s_7_28,
    s_7_29,
    s_7_30,
    s_7_31,
};

// Mes 8
static const char s_8_1[] PROGMEM = "S. Alfonso de Ligorio";
static const char s_8_2[] PROGMEM = "Ntra. Sra. de Angeles";
static const char s_8_3[] PROGMEM = "Sta. Lidia";
static const char s_8_4[] PROGMEM = "S. Juan Maria Vianney";
static const char s_8_5[] PROGMEM = "Ntra. Sra. de Nieves";
static const char s_8_6[] PROGMEM = "Transfiguracion Senor";
static const char s_8_7[] PROGMEM = "S. Cayetano";
static const char s_8_8[] PROGMEM = "Sto. Domingo de Guzman";
static const char s_8_9[] PROGMEM = "Sta. Teresa Benedicta";
static const char s_8_10[] PROGMEM = "S. Lorenzo Martir";
static const char s_8_11[] PROGMEM = "Sta. Clara de Asis";
static const char s_8_12[] PROGMEM = "Sta. Juana de Chantal";
static const char s_8_13[] PROGMEM = "S. Ponciano e Hipolito";
static const char s_8_14[] PROGMEM = "S. Maximiliano Kolbe";
static const char s_8_15[] PROGMEM = "Asuncion de la Virgen";
static const char s_8_16[] PROGMEM = "S. Esteban Hungria";
static const char s_8_17[] PROGMEM = "S. Jacinto";
static const char s_8_18[] PROGMEM = "Sta. Elena";
static const char s_8_19[] PROGMEM = "S. Juan Eudes";
static const char s_8_20[] PROGMEM = "S. Bernardo Claraval";
static const char s_8_21[] PROGMEM = "S. Pio X";
static const char s_8_22[] PROGMEM = "Sta. Maria Reina";
static const char s_8_23[] PROGMEM = "Sta. Rosa de Lima";
static const char s_8_24[] PROGMEM = "S. Bartolome Apostol";
static const char s_8_25[] PROGMEM = "S. Luis y S. Jose Cal.";
static const char s_8_26[] PROGMEM = "S. Ceferino Namuncura";
static const char s_8_27[] PROGMEM = "Sta. Monica";
static const char s_8_28[] PROGMEM = "S. Agustin de Hipona";
static const char s_8_29[] PROGMEM = "Martirio S. Juan B.";
static const char s_8_30[] PROGMEM = "Sta. Rosa de Lima";
static const char s_8_31[] PROGMEM = "S. Ramon Nonato";
static const char* const month_8[] PROGMEM = {
    s_8_1,
    s_8_2,
    s_8_3,
    s_8_4,
    s_8_5,
    s_8_6,
    s_8_7,
    s_8_8,
    s_8_9,
    s_8_10,
    s_8_11,
    s_8_12,
    s_8_13,
    s_8_14,
    s_8_15,
    s_8_16,
    s_8_17,
    s_8_18,
    s_8_19,
    s_8_20,
    s_8_21,
    s_8_22,
    s_8_23,
    s_8_24,
    s_8_25,
    s_8_26,
    s_8_27,
    s_8_28,
    s_8_29,
    s_8_30,
    s_8_31,
};

// Mes 9
static const char s_9_1[] PROGMEM = "S. Gil y S. Arturo";
static const char s_9_2[] PROGMEM = "Sta. Ingrid";
static const char s_9_3[] PROGMEM = "S. Gregorio Magno";
static const char s_9_4[] PROGMEM = "Sta. Rosalia";
static const char s_9_5[] PROGMEM = "Sta. Teresa Calcuta";
static const char s_9_6[] PROGMEM = "S. Zacarias";
static const char s_9_7[] PROGMEM = "Sta. Regina";
static const char s_9_8[] PROGMEM = "Natividad Virgen";
static const char s_9_9[] PROGMEM = "S. Pedro Claver";
static const char s_9_10[] PROGMEM = "S. Nicolas Tolentino";
static const char s_9_11[] PROGMEM = "S. Pafnucio";
static const char s_9_12[] PROGMEM = "Dulce Nombre de Maria";
static const char s_9_13[] PROGMEM = "S. Juan Crisostomo";
static const char s_9_14[] PROGMEM = "Exaltacion Sta. Cruz";
static const char s_9_15[] PROGMEM = "Ntra. Sra. Dolores";
static const char s_9_16[] PROGMEM = "S. Cornelio y Cipriano";
static const char s_9_17[] PROGMEM = "S. Roberto Belarmino";
static const char s_9_18[] PROGMEM = "S. Jose Cupertino";
static const char s_9_19[] PROGMEM = "S. Jenaro";
static const char s_9_20[] PROGMEM = "S. Andres Kim";
static const char s_9_21[] PROGMEM = "S. Mateo Evangelista";
static const char s_9_22[] PROGMEM = "S. Mauricio";
static const char s_9_23[] PROGMEM = "S. Pio de Pietrelcina";
static const char s_9_24[] PROGMEM = "Ntra. Sra. de la Merced";
static const char s_9_25[] PROGMEM = "S. Cleofas";
static const char s_9_26[] PROGMEM = "S. Cosme y Damian";
static const char s_9_27[] PROGMEM = "S. Vicente de Paul";
static const char s_9_28[] PROGMEM = "S. Wenceslao";
static const char s_9_29[] PROGMEM = "Santos Arcangeles";
static const char s_9_30[] PROGMEM = "S. Jeronimo";
static const char* const month_9[] PROGMEM = {
    s_9_1,
    s_9_2,
    s_9_3,
    s_9_4,
    s_9_5,
    s_9_6,
    s_9_7,
    s_9_8,
    s_9_9,
    s_9_10,
    s_9_11,
    s_9_12,
    s_9_13,
    s_9_14,
    s_9_15,
    s_9_16,
    s_9_17,
    s_9_18,
    s_9_19,
    s_9_20,
    s_9_21,
    s_9_22,
    s_9_23,
    s_9_24,
    s_9_25,
    s_9_26,
    s_9_27,
    s_9_28,
    s_9_29,
    s_9_30,
};

// Mes 10
static const char s_10_1[] PROGMEM = "Sta. Teresita Nino Jesus";
static const char s_10_2[] PROGMEM = "Santos Angeles Cust.";
static const char s_10_3[] PROGMEM = "S. Francisco de Borja";
static const char s_10_4[] PROGMEM = "S. Francisco de Asis";
static const char s_10_5[] PROGMEM = "Sta. Faustina Kowalska";
static const char s_10_6[] PROGMEM = "S. Bruno";
static const char s_10_7[] PROGMEM = "Ntra. Sra. del Rosario";
static const char s_10_8[] PROGMEM = "S. Hugo de Genova";
static const char s_10_9[] PROGMEM = "S. Dionisio y S. Juan";
static const char s_10_10[] PROGMEM = "Sto. Tomas Villanueva";
static const char s_10_11[] PROGMEM = "S. Juan XXIII";
static const char s_10_12[] PROGMEM = "Ntra. Sra. del Pilar";
static const char s_10_13[] PROGMEM = "S. Eduardo";
static const char s_10_14[] PROGMEM = "S. Calixto I";
static const char s_10_15[] PROGMEM = "Sta. Teresa de Jesus";
static const char s_10_16[] PROGMEM = "Sta. Margarita Alacoque";
static const char s_10_17[] PROGMEM = "S. Ignacio Antioquia";
static const char s_10_18[] PROGMEM = "S. Lucas Evangelista";
static const char s_10_19[] PROGMEM = "S. Juan de Brebeuf";
static const char s_10_20[] PROGMEM = "Sta. Irene";
static const char s_10_21[] PROGMEM = "Sta. Ursula";
static const char s_10_22[] PROGMEM = "S. Juan Pablo II";
static const char s_10_23[] PROGMEM = "S. Juan de Capistrano";
static const char s_10_24[] PROGMEM = "S. Antonio M. Claret";
static const char s_10_25[] PROGMEM = "S. Crispino";
static const char s_10_26[] PROGMEM = "S. Evaristo";
static const char s_10_27[] PROGMEM = "S. Frumencio";
static const char s_10_28[] PROGMEM = "S. Simon y Judas Tadeo";
static const char s_10_29[] PROGMEM = "S. Narciso";
static const char s_10_30[] PROGMEM = "S. Marcelo";
static const char s_10_31[] PROGMEM = "S. Alonso Rodriguez";
static const char* const month_10[] PROGMEM = {
    s_10_1,
    s_10_2,
    s_10_3,
    s_10_4,
    s_10_5,
    s_10_6,
    s_10_7,
    s_10_8,
    s_10_9,
    s_10_10,
    s_10_11,
    s_10_12,
    s_10_13,
    s_10_14,
    s_10_15,
    s_10_16,
    s_10_17,
    s_10_18,
    s_10_19,
    s_10_20,
    s_10_21,
    s_10_22,
    s_10_23,
    s_10_24,
    s_10_25,
    s_10_26,
    s_10_27,
    s_10_28,
    s_10_29,
    s_10_30,
    s_10_31,
};

// Mes 11
static const char s_11_1[] PROGMEM = "Todos los Santos";
static const char s_11_2[] PROGMEM = "Fieles Difuntos";
static const char s_11_3[] PROGMEM = "S. Martin de Porres";
static const char s_11_4[] PROGMEM = "S. Carlos Borromeo";
static const char s_11_5[] PROGMEM = "Sta. Isabel y Zacarias";
static const char s_11_6[] PROGMEM = "S. Severo";
static const char s_11_7[] PROGMEM = "S. Ernesto";
static const char s_11_8[] PROGMEM = "S. Adeodato";
static const char s_11_9[] PROGMEM = "Dedicacion B. Letran";
static const char s_11_10[] PROGMEM = "S. Leon Magno";
static const char s_11_11[] PROGMEM = "S. Martin de Tours";
static const char s_11_12[] PROGMEM = "S. Josafat";
static const char s_11_13[] PROGMEM = "S. Leandro de Sevilla";
static const char s_11_14[] PROGMEM = "S. Serapio";
static const char s_11_15[] PROGMEM = "S. Alberto Magno";
static const char s_11_16[] PROGMEM = "Sta. Gertrudis";
static const char s_11_17[] PROGMEM = "Sta. Isabel de Hungria";
static const char s_11_18[] PROGMEM = "Dedicacion Pedro y Pablo";
static const char s_11_19[] PROGMEM = "S. Crispino Viterbo";
static const char s_11_20[] PROGMEM = "S. Felix de Valois";
static const char s_11_21[] PROGMEM = "Presentacion Virgen";
static const char s_11_22[] PROGMEM = "Sta. Cecilia";
static const char s_11_23[] PROGMEM = "S. Clemente I";
static const char s_11_24[] PROGMEM = "S. Andres Dung-Lac";
static const char s_11_25[] PROGMEM = "Sta. Catalina Alejandria";
static const char s_11_26[] PROGMEM = "S. Leonardo";
static const char s_11_27[] PROGMEM = "Medalla Milagrosa";
static const char s_11_28[] PROGMEM = "S. Jaime de la Marca";
static const char s_11_29[] PROGMEM = "S. Saturnino";
static const char s_11_30[] PROGMEM = "S. Andres Apostol";
static const char* const month_11[] PROGMEM = {
    s_11_1,
    s_11_2,
    s_11_3,
    s_11_4,
    s_11_5,
    s_11_6,
    s_11_7,
    s_11_8,
    s_11_9,
    s_11_10,
    s_11_11,
    s_11_12,
    s_11_13,
    s_11_14,
    s_11_15,
    s_11_16,
    s_11_17,
    s_11_18,
    s_11_19,
    s_11_20,
    s_11_21,
    s_11_22,
    s_11_23,
    s_11_24,
    s_11_25,
    s_11_26,
    s_11_27,
    s_11_28,
    s_11_29,
    s_11_30,
};

// Mes 12
static const char s_12_1[] PROGMEM = "S. Eloy";
static const char s_12_2[] PROGMEM = "Sta. Bibiana";
static const char s_12_3[] PROGMEM = "S. Francisco Javier";
static const char s_12_4[] PROGMEM = "S. Juan Damasceno";
static const char s_12_5[] PROGMEM = "S. Sabas";
static const char s_12_6[] PROGMEM = "S. Nicolas de Bari";
static const char s_12_7[] PROGMEM = "S. Ambrosio";
static const char s_12_8[] PROGMEM = "Inmaculada Concepcion";
static const char s_12_9[] PROGMEM = "S. Juan Diego";
static const char s_12_10[] PROGMEM = "Ntra. Sra. Loreto";
static const char s_12_11[] PROGMEM = "S. Damaso I";
static const char s_12_12[] PROGMEM = "Ntra. Sra. Guadalupe";
static const char s_12_13[] PROGMEM = "Sta. Lucia";
static const char s_12_14[] PROGMEM = "S. Juan de la Cruz";
static const char s_12_15[] PROGMEM = "Sta. Cristiana";
static const char s_12_16[] PROGMEM = "Sta. Adelaida";
static const char s_12_17[] PROGMEM = "S. Lazaro";
static const char s_12_18[] PROGMEM = "Ntra. Sra. Esperanza";
static const char s_12_19[] PROGMEM = "S. Urbano V";
static const char s_12_20[] PROGMEM = "Sto. Domingo Silos";
static const char s_12_21[] PROGMEM = "S. Pedro Canisio";
static const char s_12_22[] PROGMEM = "Sta. Francisca Cabrini";
static const char s_12_23[] PROGMEM = "S. Juan de Kenty";
static const char s_12_24[] PROGMEM = "Nochebuena";
static const char s_12_25[] PROGMEM = "Natividad del Senor";
static const char s_12_26[] PROGMEM = "S. Esteban Protomartir";
static const char s_12_27[] PROGMEM = "S. Juan Evangelista";
static const char s_12_28[] PROGMEM = "Santos Inocentes";
static const char s_12_29[] PROGMEM = "Sto. Tomas Becket";
static const char s_12_30[] PROGMEM = "Sagrada Familia";
static const char s_12_31[] PROGMEM = "S. Silvestre I";
static const char* const month_12[] PROGMEM = {
    s_12_1,
    s_12_2,
    s_12_3,
    s_12_4,
    s_12_5,
    s_12_6,
    s_12_7,
    s_12_8,
    s_12_9,
    s_12_10,
    s_12_11,
    s_12_12,
    s_12_13,
    s_12_14,
    s_12_15,
    s_12_16,
    s_12_17,
    s_12_18,
    s_12_19,
    s_12_20,
    s_12_21,
    s_12_22,
    s_12_23,
    s_12_24,
    s_12_25,
    s_12_26,
    s_12_27,
    s_12_28,
    s_12_29,
    s_12_30,
    s_12_31,
};

static const char* const* const ALL_MONTHS[] PROGMEM = {
    month_1, month_2, month_3, month_4, month_5, month_6,
    month_7, month_8, month_9, month_10, month_11, month_12
};

static const uint8_t MONTH_DAYS[] = {
    31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

void getSaintOfTheDay(int day, int month, char* buffer, size_t maxLen) {
    if (!buffer || maxLen == 0) return;
    buffer[0] = '\0';

    if (month < 1 || month > 12) return;
    uint8_t maxDays = MONTH_DAYS[month - 1];
    if (day < 1 || day > maxDays) return;

    // Obtener puntero de la lista del mes desde PROGMEM
    const char* const* mTable = (const char* const*)pgm_read_ptr(&(ALL_MONTHS[month - 1]));
    if (!mTable) return;

    // Obtener puntero del string del santo desde PROGMEM
    const char* strPtr = (const char*)pgm_read_ptr(&(mTable[day - 1]));
    if (!strPtr) return;

    // Copiar desde Flash a RAM
    strncpy_P(buffer, strPtr, maxLen - 1);
    buffer[maxLen - 1] = '\0';
}
