package com.locators.wero.localizador;

import java.io.Serializable;

/**
 * Created by wero on 28/10/2017.
 */

public class Dispositivo implements Serializable {
    private String nombre;
    private String key;

    public Dispositivo(String nombre, String key){
        this.nombre = nombre;
        this.key = key;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public String getKey() {
        return key;
    }

    public void setKey(String key) {
        this.key = key;
    }
}
