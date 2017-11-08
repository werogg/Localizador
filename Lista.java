//En aquesta part es dona el nom a l'arxiu, s'estableixen enllaços d'arxius i es carreguen llibreries
package com.locators.wero.localizador;

import android.content.Context;
import android.content.Intent;
import android.os.StrictMode;
import android.renderscript.ScriptGroup;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

//Començem crean una clase pública amb el nom Lista la qual utilitza llibreries AppCompatActivity
public class Lista extends AppCompatActivity {
    
    //Inicialitzem la llista amb objectes
    ListView listView;
    //Creem la llista de valors que utilitzarà la llista d'objectes
    ArrayList<String> valores = new ArrayList<>();

    //Aquesta funció estableix l'informació que ha d'utilitzar l'aplicació per omplir els camps de cada localitzador i establir l'estil
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list);

        listView = (ListView) findViewById(R.id.Lista);

        File file = new File(String.valueOf(getApplicationContext().getFilesDir()));
        File[] listoffiles = file.listFiles();

        for (File f : listoffiles){
            if (f.getPath().endsWith(".disp")) valores.add(f.getName().substring(0, f.getName().length() - 5));
        }

        System.out.println(valores);

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_expandable_list_item_1, valores);

        listView.setAdapter(adapter);

        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                Intent intent = new Intent(view.getContext(), MapsActivity.class);
                System.out.println(valores.get(i));
                intent.putExtra("dispositivo", valores.get(i));
                startActivity(intent);
            }
        });

        registerForContextMenu(listView);

        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
    }

    //Aquesta funció s'executa al mantener premut un dels localitzadors
    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {
        if (v.getId() == R.id.Lista) {
            AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo) menuInfo;
            menu.setHeaderTitle(valores.get(info.position));
            String[] menuItems = getResources().getStringArray(R.array.menu);
            for (int i = 0; i < menuItems.length; i++) {
                menu.add(Menu.NONE, i, i, menuItems[i]);
            }
        }
    }
    
    
    //Aquesta funció inicia el programa PHP per canviar la variable buzzing (si esta sonant) y posarla a 1 durant 15 segons
    public void activateBuzzer(String adr) throws IOException {
        URL url = new URL(adr);

        InputStream in = url.openStream();
    }
    
    
    //Aquesta funció detecta les accions dins del menú de context creat al mantenir un localitzador premut
    @Override
    public boolean onContextItemSelected(MenuItem item) {
        AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo) item.getMenuInfo();
        int menuItemIndex = item.getItemId();
        String[] menuItems = getResources().getStringArray(R.array.menu);
        String selectedWord = ((TextView) info.targetView).getText().toString();
        int selectedWordId = item.getItemId();
        Dispositivo dispositivo = null;
        System.out.println(Arrays.toString(new File(String.valueOf(getApplicationContext().getFilesDir())).listFiles()));
        try {
            FileInputStream fis = new FileInputStream(String.valueOf(getApplicationContext().getFilesDir()) + "/" + selectedWord + ".disp");
            ObjectInputStream ois = new ObjectInputStream(fis);
            dispositivo = (Dispositivo) ois.readObject();
            fis.close();
            ois.close();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        if (selectedWordId == 0) {
            try {
                if (dispositivo != null) {
                    activateBuzzer("http://foro.battlepvpmine.es/activate_buzzing.php?key=" + dispositivo.getKey());
                }
                else{
                    throw new IOException();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        } else if (selectedWordId == 1) {
            File file = new File(getApplicationContext().getFilesDir(), selectedWord + ".disp");
            boolean deleted = file.delete();
            if (deleted) {
                finish();
                startActivity(getIntent());
            }
            else{
                Toast.makeText(this, "No se ha podido borrar el localizador", Toast.LENGTH_SHORT).show();
            }
        }

        return true;
    }
}
