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

public class Add extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add);
    }

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
                //https://battlepvpmine.es/write_data.php?longitude=3.10&latitude=3.4&key=8A621E21A96A6E36
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
