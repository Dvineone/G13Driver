# G13Driver

<h2>Description</h2>

<p>This device has no driver support for Linux and Logitech has no plans on creating one. So i decided to develop one myself. This driver is has basic functionality 
allowing the G-Keys to be mapped to keyboard inputs. The Mappings are hard coded ATM but I have plans to implement functionality so this can be read in from a config file.</p>

<h2>TODO'S</h2>
<ul>
  <li>Implement functionality for custom G-Key mapping via a configuration file.</li>
  <li>Implement functionality for Joystick mapping.</li>
  <li>Implement functionality for Joystick buttons.</li>
  <li>Implement functionality for LCD ouput. Adding Custom images to LCD display</li>
  <li>Implement functionality for Profiles</li>
  <li>Implement functionality for Macro Recording</li>
  <li>Implement functionality for G-Key Macro execution</li>
</ul>

<h2>Compatibility</h2>
<ul>
  <li>OS: Ubuntu Bionic Beaver - Kernel: 4.15.0-55-generic</li>
  <li>OS: Ubuntu Bionic Beaver - Kernel: 5.0.0-25-generic</li>
</ul>

<h2>Install</h2>
<b>NOTE: The file 99_rebind_g13.rules can cause your keyboard/mouse to not work after reboot.
This issue should be worked out since it should only match to the G13 device. However if you reboot and your mouse/keyboard is not working this could be the cause. This can be fixed by booting to a 
linux live boot disc and removeing the file from the directory.</b>

<ul>
  <li>1: git clone https://github.com/Dvineone/G13Driver.git</li>
  <li>2: cd G13Driver</li>
  <li>3: make</li>
  <li>4: sudo cp g13_driver.ko /lib/modules/`uname -r`/kernel/drivers/hid</li>
  <li>5: sudo echo g13_driver >> /etc/modules-load.d/modules.conf</li>
  <li>6: sudo depmod -a</li>
  <li>7: sudo modprobe g13_driver</li>
  <li>8: sudp cp 99_rebind_g13.rules /etc/udev/rules.d</li>
</ul>
