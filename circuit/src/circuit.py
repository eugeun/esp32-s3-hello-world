# schemdraw's type hints make .at() return the base Element, whose up()/down()/... take no
# length argument, although the real classes accept one. Silence that false positive.
# pyright: reportCallIssue=false
from pathlib import Path

import schemdraw
import schemdraw.elements as elm

# Output goes to ../assets/lamp.png, regardless of the current directory
OUTPUT = Path(__file__).resolve().parent.parent / 'assets' / 'lamp.png'
OUTPUT.parent.mkdir(exist_ok=True)

left_names  = ['3.3V','EN','4','5','6','7','15','16','17','18','8','3','46','9','10','11','12','13','14','5V']
right_names = ['TX','RX','1','2','42','41','40','39','38','37','36','35','0','45','48','47','21','20','19','GND']

# Schemdraw places left/right pins bottom-to-top, so reverse to read top-to-bottom
pins  = [elm.IcPin(name=n, side='left',  anchorname=f'L{n}') for n in reversed(left_names)]
pins += [elm.IcPin(name=n, side='right', anchorname=f'R{n}') for n in reversed(right_names)]
pins += [elm.IcPin(name='', side='top', anchorname='T5V'),
         elm.IcPin(name='', side='top', anchorname='TEXT'),
         elm.IcPin(name='GND', side='bottom', anchorname='BGND')]

with schemdraw.Drawing(file=str(OUTPUT), dpi=130, show=False):
    esp = elm.Ic(pins=pins, pinspacing=0.6, size=(8, 12.6), leadlen=0.8, lblsize=11,
                 label='ESP32-S3 WROOM\nGPIO Extension')

    # top pin names set by hand: the pins sit too close together for in-body labels
    elm.Label().at((esp.T5V.x - 0.45, esp.T5V.y - 1.1)).label('5V')
    elm.Label().at((esp.TEXT.x + 0.7, esp.TEXT.y - 1.1)).label('EXT-3.3V')

    # --- power / ground of the module ---
    elm.Line().at(esp.TEXT).up(0.8)
    elm.Vdd().label('3.3V')
    elm.Line().at(esp.BGND).down(0.8)
    elm.Ground()

    # --- left: pull-up + button, wired to GPIO13 through R3 ---
    elm.Line().at(esp.L13).left(1.0)
    elm.Line().up(9 * 0.6)                       # up to the node row
    elm.Resistor().left(2.5).label('R3\n10kΩ')
    node = elm.Dot()
    elm.Resistor().up(2.5).label('R2\n10kΩ')     # pull-up
    elm.Vdd().label('3.3V')
    elm.Button().at(node.start).down(2.0).label('S1', loc='right', ofst=(1.2, -0.45))
    elm.Ground()

    # --- right: GPIO2 -> R1 -> LED -> GND ---
    elm.Line().at(esp.R2).right(1.5)
    elm.Resistor().down(2.0).label('R1\n220Ω')
    elm.LED().down(2.0).label('LED1\nRed (633nm)').color('red')
    elm.Ground()