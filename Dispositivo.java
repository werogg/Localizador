//En aquesta part es dona el nom a l'arxiu, s'estableixen enllaços d'arxius i es carreguen llibreries
package com.locators.wero.localizador;

import java.io.Serializable;

//Començem crean una clase pública amb el nom Dispositivo la qual utilitza llibreries Serializable
public class Dispositivo implements Serializable {
    //Inicialitzem les variables de nom i clau
    private String nombre;
    private String key;
    
    //Fem un constructor per gestionar l'informació
    public Dispositivo(String nombre, String key){
        this.nombre = nombre;
        this.key = key;
    }

    //Funció per rebre el nom del dispositiu
    public String getNombre() {
        return nombre;
    }

    //Funcio per establir el nom desde altres clases
    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    //Funció per rebre la clau secreta
    public String getKey() {
        return key;
    }

    //Funcio per establir la clau secreta
    public void setKey(String key) {
        this.key = key;
    }
}
