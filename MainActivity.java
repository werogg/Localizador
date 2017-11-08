package com.locators.wero.localizador;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void seeList(View view){
        Intent intent = new Intent(view.getContext(), Lista.class);
        startActivity(intent);
    }

    public void seeAdd(View view){
        Intent intent = new Intent(view.getContext(), Add.class);
        startActivity(intent);
    }
}
