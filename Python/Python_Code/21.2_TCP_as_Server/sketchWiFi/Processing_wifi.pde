import controlP5.*;
import processing.net.*;

ControlP5 cp5;
Server myServer;
Client myClient;
int radioFlag = 0;  // 1 for server mode, 2 for client mode
int send_flag = 1;

color backgroundColor = color(40, 44, 52);
color textColor = color(255, 255, 255);
color fieldColor = color(30, 34, 42);
color highlightColor = color(97, 175, 239);

void setup() {
    size(800, 600);
    smooth();
    noStroke();

    cp5 = new ControlP5(this);

    setupTabs();
    setupServerUI();
    setupClientUI();
    setupGlobalUI();

    // Set default Local IP for server
    cp5.get(Textfield.class, "Local IP").setText(Server.ip());
}

void draw() {
    background(backgroundColor);
    handleServerMode();
    handleClientMode();
}

void setupTabs() {
    cp5.addTab("default")
        .activateEvent(true)
        .setHeight(40)
        .setWidth(150)
        .setLabel("TCP Server")
        .setId(1)
        .setColorBackground(fieldColor)
        .setColorLabel(textColor)
        .setColorActive(highlightColor);

    cp5.addTab("TCP Client")
        .activateEvent(true)
        .setHeight(40)
        .setWidth(150)
        .setId(2)
        .setColorBackground(fieldColor)
        .setColorLabel(textColor)
        .setColorActive(highlightColor);
}

void setupServerUI() {
    cp5.addTextfield("Local IP")
        .setPosition(30, 60)
        .setSize(200, 50)
        .setFont(createFont("Arial", 18))
        .setColor(textColor)
        .setColorLabel(textColor)
        .setColorBackground(fieldColor)
        .setColorForeground(highlightColor)
        .moveTo("default");

    cp5.addTextfield("Local PORT")
        .setPosition(30, 150)
        .setSize(200, 50)
        .setFont(createFont("Arial", 18))
        .setColor(textColor)
        .setColorLabel(textColor)
        .setColorBackground(fieldColor)
        .setColorForeground(highlightColor)
        .setText("8888")
        .moveTo("default");

    cp5.addRadioButton("connectServer")
        .setPosition(30, 240)
        .setSize(120, 30)
        .addItem("Listening", 1)
        .setColorLabel(textColor)
        .setColorActive(highlightColor)
        .setColorBackground(fieldColor)
        .moveTo("default")
        .plugTo(this, "toggleServerConnection");
}

void setupClientUI() {
    cp5.addTextfield("Remote IP")
        .setPosition(30, 60)
        .setSize(200, 50)
        .setFont(createFont("Arial", 18))
        .setColor(textColor)
        .setColorLabel(textColor)
        .setColorBackground(fieldColor)
        .setColorForeground(highlightColor)
        .setText("192.168.1.xxx")
        .moveTo("TCP Client");

    cp5.addTextfield("Remote PORT")
        .setPosition(30, 150)
        .setSize(200, 50)
        .setFont(createFont("Arial", 18))
        .setColor(textColor)
        .setColorLabel(textColor)
        .setColorBackground(fieldColor)
        .setColorForeground(highlightColor)
        .setText("80")
        .moveTo("TCP Client");

    cp5.addRadioButton("connectClient")
        .setPosition(30, 240)
        .setSize(120, 30)
        .addItem("Connect Server", 1)
        .setColorLabel(textColor)
        .setColorActive(highlightColor)
        .setColorBackground(fieldColor)
        .moveTo("TCP Client")
        .plugTo(this, "toggleClientConnection");
}

void setupGlobalUI() {
    cp5.addTextarea("recvData")
        .setPosition(250, 60)
        .setSize(500, 200)
        .setFont(createFont("Arial", 16))
        .setColor(textColor)
        .setColorBackground(fieldColor)
        .scroll(20)
        .setColorForeground(highlightColor)
        .moveTo("global");

    cp5.addTextfield("sendData")
        .setPosition(250, 300)
        .setSize(500, 100)
        .setFont(createFont("Arial", 16))
        .setColor(textColor)
        .setLabel("")
        .setFocus(true)
        .setColorBackground(fieldColor)
        .setColorForeground(highlightColor)
        .moveTo("global");

    cp5.addButton("clearRecv")
        .setValue(0)
        .setPosition(250, 270)
        .setSize(120, 30)
        .setColorLabel(textColor)
        .setColorBackground(fieldColor)
        .setColorForeground(highlightColor)
        .moveTo("global")
        .plugTo(this, "clearRecv");

    cp5.addButton("clearSend")
        .setValue(0)
        .setPosition(250, 410)
        .setSize(120, 30)
        .setColorLabel(textColor)
        .setColorBackground(fieldColor)
        .setColorForeground(highlightColor)
        .moveTo("global")
        .plugTo(this, "clearSend");

    cp5.addButton("Send")
        .setValue(0)
        .setPosition(630, 410)
        .setSize(120, 30)
        .setColorLabel(textColor)
        .setColorBackground(fieldColor)
        .setColorForeground(highlightColor)
        .plugTo(this, "sendDataToClientOrServer")
        .moveTo("global");
}

void handleServerMode() {
    if (radioFlag == 1 && myServer != null) {
        Client client = myServer.available();
        if (client != null) {
            String receivedData = client.readString();
            if (receivedData != null) {
                String message = client.ip() + ": " + receivedData;
                cp5.get(Textarea.class, "recvData").append(message + "\n");
                println("Server received: " + message);  // Debug output
            }
        }
    }
}

void handleClientMode() {
    if (radioFlag == 2 && myClient != null && myClient.available() > 0) {
        String receivedData = myClient.readString();
        if (receivedData != null) {
            String message = cp5.get(Textfield.class, "Remote IP").getText() + ": " + receivedData;
            cp5.get(Textarea.class, "recvData").append(message + "\n");
            println("Client received: " + message);  // Debug output
        }
    }
}

void toggleServerConnection(int a) {
    radioFlag = a == 1 ? 1 : 0;
    if (radioFlag == 1) {
        startServer();
    } else {
        stopServer();
    }
}

void toggleClientConnection(int a) {
    radioFlag = a == 1 ? 2 : 0;
    if (radioFlag == 2) {
        startClient();
    } else {
        stopClient();
    }
}

void startServer() {
    int port = int(cp5.get(Textfield.class, "Local PORT").getText());
    myServer = new Server(this, port);
    cp5.get(Textfield.class, "Local IP").setText(Server.ip());
    println("Server started on port " + port);  // Debug output
}

void stopServer() {
    if (myServer != null) {
        myServer.stop();
        println("Server stopped");  // Debug output
    }
}

void startClient() {
    String ip = cp5.get(Textfield.class, "Remote IP").getText();
    int port = int(cp5.get(Textfield.class, "Remote PORT").getText());
    if (!ip.equals("192.168.1.xxx")) {
        myClient = new Client(this, ip, port);
        println("Client connected to " + ip + ":" + port);  // Debug output
    } else {
        println("Invalid IP address");  // Debug output
    }
}

void stopClient() {
    if (myClient != null) {
        myClient.stop();
        println("Client disconnected");  // Debug output
    }
}

void sendDataToClientOrServer() {
    String message = cp5.get(Textfield.class, "sendData").getText();
    if (radioFlag == 1 && myServer != null) {
        myServer.write(message);
        println("Server sent: " + message);  // Debug output
    } else if (radioFlag == 2 && myClient != null) {
        myClient.write(message);
        println("Client sent: " + message);  // Debug output
    }
    cp5.get(Textfield.class, "sendData").clear();
}

void clearRecv() {
    cp5.get(Textarea.class, "recvData").clear();
}

void clearSend() {
    cp5.get(Textfield.class, "sendData").clear();
}
