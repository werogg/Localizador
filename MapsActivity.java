package com.locators.wero.localizador;

import android.os.AsyncTask;
import android.os.StrictMode;
import android.support.v4.app.FragmentActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.Reader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import javax.net.ssl.HttpsURLConnection;

public class MapsActivity extends FragmentActivity implements OnMapReadyCallback {

    private GoogleMap mMap;

    Dispositivo dispositivo;

    Double longitude;

    Double latitude;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
    }


    /**
     * Manipulates the map once available.
     * This callback is triggered when the map is ready to be used.
     * This is where we can add markers or lines, add listeners or move the camera. In this case,
     * we just add a marker near Sydney, Australia.
     * If Google Play services is not installed on the device, the user will be prompted to install
     * it inside the SupportMapFragment. This method will only be triggered once the user has
     * installed Google Play services and returned to the app.
     */
    @Override
    public void onMapReady(GoogleMap googleMap) {
        try {
            String disp = getIntent().getExtras().getString("dispositivo");
            System.out.println("dispositivo: " + disp);
            for (String s : getApplicationContext().getFilesDir().list()){
                System.out.println(s);
            };
            FileInputStream fis = new FileInputStream(getFilesDir().toString() + File.separator + disp + ".disp");
            ObjectInputStream ois = new ObjectInputStream(fis);
            dispositivo = (Dispositivo) ois.readObject();
            fis.close();
            ois.close();
            getLongitude();
            getLatitude();
        }
        catch (IOException | ClassNotFoundException | NullPointerException e) {
            e.printStackTrace();
        }
        mMap = googleMap;

        // Add a marker in Sydney and move the camera
        LatLng posDevice = new LatLng(latitude, longitude);
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(posDevice, 16));
        mMap.addMarker(new MarkerOptions().position(posDevice).title("Posicion del dispositivo"));
    }

    public void getLatitude() throws IOException {
        URL url = new URL("http://foro.battlepvpmine.es/get_latitude.php?key=" + dispositivo.getKey());

        InputStream in = url.openStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(in));
        latitude = Double.valueOf(reader.readLine());

    }

    public void getLongitude() throws IOException {
        System.out.println(dispositivo.getKey());
        URL url = new URL("http://foro.battlepvpmine.es/get_longitude.php?key=" + dispositivo.getKey());

        InputStream in = url.openStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(in));
        longitude = Double.valueOf(reader.readLine());
    }
}
