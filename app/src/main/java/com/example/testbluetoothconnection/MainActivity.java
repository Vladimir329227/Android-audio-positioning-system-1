package com.example.testbluetoothconnection;

import static android.content.ContentValues.TAG;
import static java.lang.Math.abs;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.AudioTrack;
import android.media.MediaPlayer;
import android.media.MediaRecorder;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import java.io.DataInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;
import java.util.List;
import java.util.Set;
import java.util.UUID;

public class MainActivity extends AppCompatActivity implements SensorEventListener {

    static {
        System.loadLibrary("testbluetoothconnection");
    }

    public static native double[] argInit_real_T(double[] inp1, double[] inp2, int razm1, int razm2);

    public Button buttun_t;
    public Button buttun_conneckt;
    public Button buttun_zvuk;
    public Button buttun_find_zvuk;
    public TextView text_t;
    public ImageView imageView;
    public boolean IsOn = false;
    private String deviceName = null;
    private String deviceAddress;
    public static Handler handler;
    public static BluetoothSocket mmSocket;
    public static ConnectedThread connectedThread = null;
    public static CreateConnectThread createConnectThread;
    public BluetoothAdapter bluetoothAdapter;
    private final static int CONNECTING_STATUS = 1; // used in bluetooth handler to identify message status
    private final static int MESSAGE_READ = 2; // used in bluetooth handler to identify message update

    SensorManager mSensorManager;
    /** Создали объект типа сенсор для получения данных угла наклона телефона */
    Sensor mAccelerometerSensor;
    Sensor mMagneticFieldSensor;

    private TextView xyView;
    private TextView xzView;
    private TextView zyView;

    MediaPlayer mPlayer;
    private long cur_time = 0;
    private long paus_time = (long) 1000000000;

    @Override
    protected void onPause() {
        //говорим что данные будем получать из этого окласса
        mSensorManager.unregisterListener(this);
        super.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        //регистрируем сенсоры в объекты сенсора
        mSensorManager.registerListener(this, mAccelerometerSensor, SensorManager.SENSOR_DELAY_GAME);
        mSensorManager.registerListener(this, mMagneticFieldSensor, SensorManager.SENSOR_DELAY_GAME);
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        //создали массив в которые будем записывать наши данные полученые с датчиков
        float[] values = event.values;
        switch (event.sensor.getType()) {
            case Sensor.TYPE_ACCELEROMETER: {
                //собственно выводим все полученые параметры в текствьюшки наши
                xyView.setText(String.format("%1.3f", event.values[SensorManager.DATA_X]));
                xzView.setText(String.format("%1.3f", event.values[SensorManager.DATA_Y]));
                zyView.setText(String.format("%1.3f", event.values[SensorManager.DATA_Z]));
                if (connectedThread != null && abs(cur_time - event.timestamp) > paus_time) {
                    zyView.setText("OK");

                    connectedThread.write(String.format("%1.2f", event.values[SensorManager.DATA_X]) + '/'
                            + String.format("%1.2f", event.values[SensorManager.DATA_Y]) +
                            '/' + String.format("%1.2f", event.values[SensorManager.DATA_Z]));
                    cur_time = event.timestamp;

                }
            }
            break;
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }

    public boolean isReading = false;
    public int myBufferSize = 8192;
    public AudioRecord audioRecord;

    void createAudioRecorder() {
        int sampleRate = chastota;
        int channelConfig = AudioFormat.CHANNEL_IN_MONO;
        int audioFormat = AudioFormat.ENCODING_PCM_16BIT;

        int minInternalBufferSize = AudioRecord.getMinBufferSize(sampleRate,
                channelConfig, audioFormat);

        int internalBufferSize = minInternalBufferSize * 10;
        Log.d(TAG, "minInternalBufferSize = " + minInternalBufferSize
                + ", internalBufferSize = " + internalBufferSize
                + ", myBufferSize = " + myBufferSize);

        if (ActivityCompat.checkSelfPermission(this, android.Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED) {
            audioRecord = new AudioRecord(MediaRecorder.AudioSource.MIC, sampleRate, channelConfig, audioFormat, myBufferSize);
            return;
        }
        audioRecord = new AudioRecord(MediaRecorder.AudioSource.MIC, sampleRate, channelConfig, audioFormat, myBufferSize);
    }

    int razmer = 96000;
    int chastota = 16000;

    short[] testBuff1 = new short[razmer];
    short[] testBuff2;

    double[] inpBuff1 = new double[razmer];
    double[] inpBuff2;

    int cur_nam = 0;
    public void readStart(View v) {
        Log.d(TAG, "read start");
        audioRecord.startRecording();
        isReading = true;
        new Thread(new Runnable() {
            @Override
            public void run() {
                if (audioRecord == null){
                    Log.d(TAG, "Vse figna!!!!!!!!! ");
                    return;
                }
                short[] myBuffer = new short[myBufferSize];
                int readCount = 0;
                int totalCount = 0;
                while (isReading) {
                    readCount = audioRecord.read(myBuffer, 0, myBufferSize);
                    totalCount += readCount;
                    //add_to_file(myBuffer);
                    for (short i : myBuffer){
                        testBuff1[cur_nam%razmer] = i;
                        cur_nam++;
                    }
                    Log.d(TAG, "Rez ======= ---------- ++++++" + cur_nam);
                    if (cur_nam >= razmer)
                        break;
                    Log.d(TAG, "readCount = " + readCount + ", totalCount = "
                            + totalCount + ", Mas :" + Arrays.toString(myBuffer));
                }
            }
        }).start();
    }

    public void readStop(View v) {
        Log.d(TAG, "read stop");
        isReading = false;
    }

    public short[] readWavFile(Intent intent, int sampleRate) {
        int channelConfig = AudioFormat.CHANNEL_IN_STEREO;
        int audioFormat = AudioFormat.ENCODING_PCM_16BIT;
        int bufferSize = AudioTrack.getMinBufferSize(sampleRate, channelConfig, audioFormat);
        short[] audioData = null;

        Uri uri = intent.getData();



        try (InputStream inputStream = getContentResolver().openInputStream(uri);
             DataInputStream dataInputStream = new DataInputStream(inputStream)) {
            Log.d(TAG, "1111111111111111111111111111");

            // Пропускаем заголовок файла
            skipWavHeader(dataInputStream);

            // Читаем звуковые данные
            int bytesRead = 0;
            byte[] buffer = new byte[bufferSize];

            ByteBuffer byteBuffer = ByteBuffer.wrap(buffer).order(ByteOrder.LITTLE_ENDIAN);
            while ((bytesRead = dataInputStream.read(buffer, 0, bufferSize)) != -1) {
                byteBuffer.position(0);
                Log.d(TAG, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

                short[] shortBuffer = new short[bytesRead / 2];
                for (int i = 0; i < shortBuffer.length; i++) {
                    shortBuffer[i] = byteBuffer.getShort();

                }

                FileOutputStream fos = null;
                try {
                    testBuff2 = new short[shortBuffer.length];
                    inpBuff2 = new double[shortBuffer.length];
                    for (int i=0;i<shortBuffer.length;i++){
                        testBuff2[i] = shortBuffer[i];


                    }
                    String text =  Arrays.toString(shortBuffer);
                    fos = openFileOutput("test.txt", MODE_PRIVATE);
                    fos.write(text.getBytes());
                    Toast.makeText(this, "Файл сохранен", Toast.LENGTH_SHORT).show();
                }
                catch(IOException ex) {
                    Toast.makeText(this, ex.getMessage(), Toast.LENGTH_SHORT).show();
                }
                finally{
                    try{
                        if(fos!=null)
                            fos.close();
                    }
                    catch(IOException ex){
                        Toast.makeText(this, ex.getMessage(), Toast.LENGTH_SHORT).show();
                    }
                }
                Log.d(TAG, "2222222222222222222222222222222");

                if (audioData == null) {
                    audioData = shortBuffer;
                } else {
                    short[] temp = new short[audioData.length + shortBuffer.length];
                    System.arraycopy(audioData, 0, temp, 0, audioData.length);
                    System.arraycopy(shortBuffer, 0, temp, audioData.length, shortBuffer.length);
                    audioData = temp;
                }
            }
        } catch (IOException e) {
            Log.e("readWavFile", "Error reading wav file", e);
        }

        return audioData;
    }

    private void skipWavHeader(DataInputStream dataInputStream) throws IOException {
        // Пропускаем RIFF Header
        //String chunkID = readString(dataInputStream, 4);
        //int chunkSize = dataInputStream.readInt();
        //String format = readString(dataInputStream, 4);

        // Пропускаем fmt sub-chunk
        //String subChunk1ID = readString(dataInputStream, 4);
        //int subChunk1Size = dataInputStream.readInt();
        //dataInputStream.skipBytes(subChunk1Size);


        Log.d(TAG, "4444444444444444444444444444");


        // Пропускаем fact sub-chunk, если он есть
        // String subChunk2ID = readString(dataInputStream, 4);

        Log.d(TAG, "333333333333333333333333");


        //if (subChunk2ID.equals("fact")) {
        //    int subChunk2Size = dataInputStream.readInt();
        //    dataInputStream.skipBytes(subChunk2Size);
        //}


        // Пропускаем data sub-chunk header
        //String dataChunkID = readString(dataInputStream, 4);
        //dataInputStream.readInt();


    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == RESULT_OK) {

            Uri uri = data.getData();
            if (uri == null) {
                return;
            }
            String fileName = uri.getPath();
            try {
                InputStream in = getContentResolver().openInputStream(uri);
                Log.e("readWavFile", "******************" + (in == null));
            } catch (FileNotFoundException e) {
                throw new RuntimeException(e);
            }
            short[] audioData = readWavFile(data, chastota);
            Log.d(TAG, "++++++Mas :" + Arrays.toString(audioData));
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        xyView = (TextView) findViewById(R.id.xyValue);
        xzView = (TextView) findViewById(R.id.xzValue);
        zyView = (TextView) findViewById(R.id.zyValue);

        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        List<Sensor> sensors = mSensorManager.getSensorList(Sensor.TYPE_ALL);
        if (sensors.size() > 0) {
            for (Sensor sensor : sensors) {
                switch (sensor.getType()) {
                    case Sensor.TYPE_ACCELEROMETER:
                        if (mAccelerometerSensor == null)
                            mAccelerometerSensor = sensor;
                        break;
                    default:
                        break;
                }
            }
        }

        imageView = findViewById(R.id.imageView);
        text_t = (TextView) findViewById(R.id.text_test);
        text_t.setText("123");
        buttun_t = (Button) findViewById(R.id.button);
        buttun_conneckt = (Button) findViewById(R.id.button2);
        buttun_zvuk = (Button) findViewById(R.id.button3);
        buttun_find_zvuk = (Button) findViewById(R.id.button4);

        mPlayer = MediaPlayer.create(this, R.raw.zvuk);

        buttun_find_zvuk.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {
                text_t.setText("Ok 21/06/24");
                int resId = R.raw.test1; // replace my_audio_file with the name of your audio file
                String filePath = "android.resource://" + getPackageName() + "/" + resId;

                Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
                intent.addCategory(Intent.CATEGORY_OPENABLE);
                intent.setType("audio/*");
                startActivityForResult(intent, 666);

                createAudioRecorder();

                if (isReading){
                    readStop(v);
                }
                else {
                    readStart(v);
                }
            }
        });

        buttun_zvuk.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {
                double[] test = {1.0,1.0,1.0};

                for (int i=0;i<inpBuff1.length;i++)
                    inpBuff1[i] =  testBuff1[i];
                for (int i=0;i<inpBuff2.length;i++)
                    inpBuff2[i] =  testBuff2[i];


                Log.e(String.valueOf(200), Integer.toString(inpBuff1.length) + "_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+" + Integer.toString(inpBuff2.length));

                text_t.setText(Arrays.toString(argInit_real_T(inpBuff1, inpBuff2, inpBuff1.length, inpBuff2.length)));
                mPlayer.start();
            }
        });

        buttun_t.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                String cmdText = "";
                if (!IsOn) {
                    cmdText = "<turn on>";
                    imageView.setImageResource(R.drawable.dog_on_faer_3);
                    buttun_t.setText("Включить");
                } else {
                    cmdText = "<turn off>";
                    imageView.setImageResource(R.drawable.dog_3);
                    buttun_t.setText("Выключить");
                }
                IsOn = !IsOn;
                connectedThread.write(cmdText);
            }
        });

        handler = new Handler(Looper.getMainLooper()) {
            @Override
            public void handleMessage(Message msg){
                switch (msg.what){
                    case CONNECTING_STATUS:
                        switch(msg.arg1){
                            case 1:
                                text_t.setText("Подключено");
                                break;
                            case -1:
                                text_t.setText("Подключение не удалось");
                                break;
                        }
                        break;

                    case MESSAGE_READ:
                        String arduinoMsg = msg.obj.toString(); // Read message from Arduino
                        switch (arduinoMsg.toLowerCase()){
                            case "led is turned on":
                                text_t.setText("Сообщение от ардуинки : " + arduinoMsg);
                                break;
                            case "led is turned off":
                                text_t.setText("Сообщение от ардуинки : " + arduinoMsg);
                                break;
                        }
                        break;
                }
            }
        };

        buttun_conneckt.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                ActivityCompat.requestPermissions(MainActivity.this, new String[]{android.Manifest.permission.BLUETOOTH_CONNECT}, 1);
                text_t.setText("Проверка Bluetooth разрешений");
                if (ActivityCompat.checkSelfPermission(MainActivity.this, android.Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                    bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
                    Set<BluetoothDevice> pairedDevices = bluetoothAdapter.getBondedDevices();
                    text_t.setText("Поиск устройства");
                    String deviceName = "";
                    String deviceHardwareAddress = "";
                    if (pairedDevices.size() > 0) {
                        for (BluetoothDevice device : pairedDevices) {
                            text_t.setText(device.getName());
                            deviceName = device.getName();
                            deviceHardwareAddress = device.getAddress(); // MAC address
                            Log.e(String.valueOf(200), deviceName);
                            if (deviceName.equals("HC-05"))
                                break;
                        }
                    }
                    if (deviceName.equals("HC-05")) {
                        text_t.setText("Подключение к устройству");
                        createConnectThread = new CreateConnectThread(bluetoothAdapter, deviceHardwareAddress);
                        createConnectThread.start();
                    } else
                        text_t.setText("Устройство не найдено");
                    return;
                }
                text_t.setText("Нету нужных Bluetooth разрешений");

            }
        });
    }


    /* ============================ Thread to Create Bluetooth Connection =================================== */
    public class CreateConnectThread extends Thread {

        public CreateConnectThread(BluetoothAdapter bluetoothAdapter, String address) {
            /*
            Use a temporary object that is later assigned to mmSocket
            because mmSocket is final.
             */
            BluetoothDevice bluetoothDevice = bluetoothAdapter.getRemoteDevice(address);
            BluetoothSocket tmp = null;
            if (ActivityCompat.checkSelfPermission(MainActivity.this , android.Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                UUID uuid = bluetoothDevice.getUuids()[0].getUuid();
                try {
                /*
                Get a BluetoothSocket to connect with the given BluetoothDevice.
                Due to Android device varieties,the method below may not work fo different devices.
                You should try using other methods i.e. :
                tmp = device.createRfcommSocketToServiceRecord(MY_UUID);
                 */
                    tmp = bluetoothDevice.createInsecureRfcommSocketToServiceRecord(uuid);

                } catch (IOException e) {
                    Log.e(TAG, "Socket's create() method failed", e);
                }
                mmSocket = tmp;
            }

        }

        public void run() {
            // Cancel discovery because it otherwise slows down the connection.
            if (ActivityCompat.checkSelfPermission(MainActivity.this , android.Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
                bluetoothAdapter.cancelDiscovery();
                try {
                    // Connect to the remote device through the socket. This call blocks
                    // until it succeeds or throws an exception.
                    mmSocket.connect();
                    Log.e("Status", "Device connected");
                    handler.obtainMessage(CONNECTING_STATUS, 1, -1).sendToTarget();
                } catch (IOException connectException) {
                    // Unable to connect; close the socket and return.
                    try {
                        mmSocket.close();
                        Log.e("Status", "Cannot connect to device");
                        handler.obtainMessage(CONNECTING_STATUS, -1, -1).sendToTarget();
                    } catch (IOException closeException) {
                        Log.e(TAG, "Could not close the client socket", closeException);
                    }

                    return;
                }
            }

            // The connection attempt succeeded. Perform work associated with
            // the connection in a separate thread.
            connectedThread = new ConnectedThread(mmSocket);
            connectedThread.run();
        }

        // Closes the client socket and causes the thread to finish.
        public void cancel() {
            try {
                mmSocket.close();
            } catch (IOException e) {
                Log.e(TAG, "Could not close the client socket", e);
            }
        }
    }

    /* =============================== Thread for Data Transfer =========================================== */
    public static class ConnectedThread extends Thread {
        private final BluetoothSocket mmSocket;
        private final InputStream mmInStream;
        private final OutputStream mmOutStream;

        public ConnectedThread(BluetoothSocket socket) {
            mmSocket = socket;
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            // Get the input and output streams, using temp objects because
            // member streams are final
            try {
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            } catch (IOException e) { }

            mmInStream = tmpIn;
            mmOutStream = tmpOut;
        }

        public void run() {
            byte[] buffer = new byte[1024];  // buffer store for the stream
            int bytes = 0; // bytes returned from read()
            // Keep listening to the InputStream until an exception occurs
            while (true) {
                try {
                    /*
                    Read from the InputStream from Arduino until termination character is reached.
                    Then send the whole String message to GUI Handler.
                     */
                    buffer[bytes] = (byte) mmInStream.read();
                    String readMessage;
                    if (buffer[bytes] == '\n'){
                        readMessage = new String(buffer,0,bytes);
                        Log.e("Arduino Message",readMessage);
                        handler.obtainMessage(MESSAGE_READ,readMessage).sendToTarget();
                        bytes = 0;
                    } else {
                        bytes++;
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                    break;
                }
            }
        }

        /* Call this from the main activity to send data to the remote device */
        public void write(String input) {
            byte[] bytes = input.getBytes(); //converts entered String into bytes
            try {
                mmOutStream.write(bytes);
            } catch (IOException e) {
                Log.e("Send Error","Unable to send message",e);
            }
        }

        /* Call this from the main activity to shutdown the connection */
        public void cancel() {
            try {
                mmSocket.close();
            } catch (IOException e) { }
        }
    }

    /* ============================ Terminate Connection at BackPress ====================== */
    @Override
    public void onBackPressed() {
        // Terminate Bluetooth Connection and close app
        if (createConnectThread != null){
            createConnectThread.cancel();
        }
        Intent a = new Intent(Intent.ACTION_MAIN);
        a.addCategory(Intent.CATEGORY_HOME);
        a.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(a);
    }
}