const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);

const { Server } = require("socket.io");
const io = new Server(server);

const { SerialPort } = require('serialport');
const port = new SerialPort({
  path: 'COM5',
  baudRate: 9600,
});
//path에 아두이노 연결된 포트, 시리얼통신 9600으로

var brightness = 0;


app.get('/', (req, res) => {
  res.sendFile(__dirname +'/public/index.html');
});
//해당 프로젝트 루트폴더 + public~~디렉토리
server.listen(8080, () => {
  console.log('listening on *:8080');
});
console.log("Web Server Started go to 'http://localhost:8080' in your Browser.");
//html 파일로 8080포트로 node 서버 열고


io.on('connection', (socket) => {
  //이벤트핸들러 -> 클라이언트와 연결이 확립될시 실행됨
  console.log('연결확인메시지')
  socket.on('led', function (data) {
    //또다른 이벤트핸들러 -> 'led'라는 이벤트를 수신하면 실행
                var brightness = data.value;
                var buf = new Buffer.alloc(1);
                buf.writeUInt8(brightness, 0);
                port.write(buf);
				
				io.sockets.emit('led', {value: brightness});   
        });
        socket.emit('led', {value: brightness});
});