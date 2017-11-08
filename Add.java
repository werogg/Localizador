//En aquesta part es dona el nom a l'arxiu, s'estableixen enllaços d'arxius i es carreguen llibreries
package com.locators.wero.localizador;

import android.content.Context;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

//Començem crean una clase pública amb el nom Add la qual utilitza llibreries d'AppCompatActivity
public class Add extends AppCompatActivity {
    
    //Aquesta part del codi serveix per la creació de l'activitat i li aplica el disseny corresponent
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add);
    }
    
    //En aquesta funció inicialitzem les variables pels camps del nom, clau secreta... i les guardem com a objecte de la llista al fer clic al botó AÑADIR
    public void save(View view) throws IOException {
        EditText nombre = (EditText) findViewById(R.id.name);
        EditText key = (EditText) findViewById(R.id.key) ;
        String sNombre = String.valueOf(nombre.getText());
        String sKey = String.valueOf(key.getText());
        Dispositivo dispositivo = new Dispositivo(sNombre, sKey);
        //System.out.println("Creando dispositivo " + dispositivo.getNombre());
        //System.out.println("Clave: " + dispositivo.getKey());
        File file = new File(getApplicationContext().getFilesDir(), sNombre + ".disp");
        if (!(sNombre.isEmpty() || sKey.isEmpty())) {
            if (!file.exists()) {
                FileOutputStream fos = openFileOutput(sNombre + ".disp", Context.MODE_PRIVATE);
                ObjectOutputStream oos = new ObjectOutputStream(fos);
                oos.writeObject(dispositivo);
                oos.close();
                fos.close();
                Toast.makeText(this, "El localizador " + sNombre + " ha sido añadido a la lista!", Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(view.getContext(), MainActivity.class);
                startActivity(intent);
            }
            else{
                Toast.makeText(this, "Un dispositivo con esta clave ya existe!", Toast.LENGTH_SHORT).show();
            }
        } else {
            Toast.makeText(this, "No puedes dejar ningún campo vacío!", Toast.LENGTH_SHORT).show();
        }

    }
}
