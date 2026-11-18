# ESP32 + DS18B20 — Smart Cellar IoT Probe

วัดอุณหภูมิถังหมักแล้วส่งเข้า NEXT SIP Batch Guardian ทุก 60 วินาที

## อุปกรณ์
- ESP32 Dev Board
- DS18B20 waterproof temperature probe
- Resistor 4.7kΩ

## การต่อวงจร

| สายโพรบ DS18B20 | ESP32 |
|---|---|
| แดง (VCC) | 3V3 |
| ดำ (GND) | GND |
| เหลือง (DATA) | GPIO4 |

ต่อ Resistor 4.7kΩ (pull-up) ระหว่างขา DATA (เหลือง) กับ 3V3

```
 3V3 ──────┬───────────── แดง (VCC)
           │
         [4.7kΩ]
           │
 GPIO4 ────┴───────────── เหลือง (DATA)
 GND  ─────────────────── ดำ (GND)
```

## Firmware
1. ติดตั้ง Arduino IDE + ESP32 board package
2. ติดตั้งไลบรารี `OneWire` และ `DallasTemperature`
3. เปิด [`next_sip_probe.ino`](next_sip_probe.ino) แก้ `ssid`, `password`, `serverApi`, `deviceKey`
4. Upload แล้วเปิด Serial Monitor (115200)

## Payload
```http
POST /api/iot/readings
Content-Type: application/json
X-Device-Key: <device key>

{"temp_c": 27.40}
```

> สถานะ: Reference design — ในเดโมปัจจุบันข้อมูลอุณหภูมิยังเป็นข้อมูลตัวอย่าง
