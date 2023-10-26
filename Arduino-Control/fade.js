const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);

const { Server } = require("socket.io");
const io = new Server(server);
const { Buffer } = require('node:buffer');
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
                var command = data.value;
                console.log(command)
                var buf = new Buffer.alloc(1);
                buf.writeUInt8(command, 0);

                /*
                var buf = Buffer.from(command, 'utf8');
                문자받으려고 시도했던거
                https://nodejs.org/api/buffer.html#buffers-and-character-encodings
                */
                
                console.log(buf)
                port.write(buf);
                //이부분이 실제로 아두이노에 시리얼로 값을 보낸다.
				
				io.sockets.emit('led', {value: brightness});   
        //여기서 클라이언트로 변경사항을 보내주는데
        //여기서 html파일의 socket.on 부분이 이벤트 수신후 실행됨.
        });
        socket.emit('led', {value: brightness});
});