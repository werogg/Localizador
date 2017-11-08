//En aquesta part es dona el nom a l'arxiu, s'estableixen enllaços d'arxius i es carreguen llibreries
package com.locators.wero.localizador;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

//Començem crean una clase pública amb el nom MainActivity la qual utilitza llibreries AppCompatActivity i aquesta serà l'activitat principal
public class MainActivity extends AppCompatActivity {

    //Aquesta funció estableix l'informació que ha d'utilitzar l'aplicació per omplir els camps de cada localitzador i aplica el disseny
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    //Aquesta funció es el codi intern del botó LISTA per accedir a la clase Lista
    public void seeList(View view){
        Intent intent = new Intent(view.getContext(), Lista.class);
        startActivity(intent);
    }

    //Aquesta funció es el codi intern del botó AÑADIR per anar a la clase Add
    public void seeAdd(View view){
        Intent intent = new Intent(view.getContext(), Add.class);
        startActivity(intent);
    }
}
