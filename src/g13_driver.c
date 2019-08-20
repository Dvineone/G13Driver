#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hid.h>

/**
 * Version Information
 * */
#define DRIVER_VERSION ""
#define DRIVER_AUTHOR "Dvineone"
#define DRIVER_DEC "USB G13 Gamepad Driver"

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DEC);
MODULE_LICENSE("GPL");


#define G13_GKEY_COUNT 22

/*
struct g13_led {
  struct led_classdev cdev;
  struct work_struct work;
  int brightness;
  bool removed;
};

struct g13_drvdata {
  unsigned long quirks;
  struct g13_led record_led; 
};
*/

// Bytes            Function
// [0]                Reserved Byte for Report ID if used 
// [1-2]              Joystick
// [3]                G1-G8
// [4]                G9-17
// [5]                G18-Light State
// [6]                Macro/Modes
// [7]                Joystick Buttons
static __u8 g13_fixed_rdesc[] = {
  0x05, 0x01,        // Global - Usage Page (Generic Desktop Ctrls)
  0x09, 0x07,        // Local - Usage (Keyboard)
  0xA1, 0x01,        // Main - Collection (Application)
  //0x15, 0x00,        //   Logical Minimum (0)
  //0x26, 0x01, 0x00, //   Logical Maximum (255) 
 
  /* Report Id
   * Byte 0 - This byte is reserved for report id if it is used.
   * We are not using it so we pad the byte.
   * */
  0x75, 0x08,        //   Report Size (8)
  0x95, 0x01,        //   Report Count (2)
  0x81, 0x01,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

  /* JoyStick Usage
   * Bytes 1-2 Map to the joystick.
   * TODO: Implement Joystick Functionality
   * */
  0x09, 0x01,        //   Usage Page (Generic Desktop)
  0x09, 0x26,        //   Usage(26)
  0x75, 0x08,        //   Report Size (8)
  0x95, 0x02,        //   Report Count (2)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  
  /* GKey Usage
   * Bytes 3-5 Map to the GKeys
   * */
  0x05, 0x07,        //   Usage Page(Kbrd/Keypad)
  0x19, 0xE0,        //   Usage Minimum (Sys Power Down)
	0x29, 0xF6,        //   Usage Maximum (Sys Wake Up)
  0x75, 0x01,        //   Report Size (1)
  0x95, 0x16,        //   Report Count (16)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  
  /* GKey Padding
   * Byte 5 - We are padding the final 2 bits for now
   * TODO: Do something with the final 2 bits of the GKey Usage
   * */
  0x75, 0x01,        //   Report Size (1)
  0x95, 0x02,        //   Report Count (2)
  0x81, 0x01,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

  /* JoyStick Buttons/Macrobuttons
   * Byte 7 - Maps to the joystick buttons
   * TODO: Implement Joystick/Marco Buttons functionality
   * */
  0x75, 0x08,        //   Report Size (8)
  0x95, 0x02,        //   Report Count (2)
  0x81, 0x01,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

  0xC0,              // End Collection
};


static __u8 g13_keycodes[G13_GKEY_COUNT] = {
  KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, 
  KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, 
         KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, 
                KEY_T, KEY_U, KEY_V,
};

// Replace the HID Report Descriptor with our custom one.
static __u8 *g13_report_fixup(struct hid_device *hdev, __u8 *rdesc, unsigned int *rsize) {
	hid_info(hdev, "fixing up G13 report descriptor\n");

	rdesc = g13_fixed_rdesc;
	*rsize = sizeof(g13_fixed_rdesc);

	return rdesc;
}

/*
 *  return 0 - Continue parsing normally
 *  return 1 - Skip parsing normally it was already handled
 *  return -1 - Skip this usage altogether
 * */
static int g13_input_mapping(struct hid_device *hdev, struct hid_input *input, struct hid_field *field, struct hid_usage *usage, unsigned long **bit, int *max) {
  int gkey; 
  
  // If the usage is not our G13 Keyboard Usage ignore it. 
  if((usage->hid & HID_USAGE_PAGE) != HID_UP_KEYBOARD) {
    return -1;
  }
  
  // Map keys to our G13 Scancodes
  gkey = (usage->hid & HID_USAGE);
  switch(gkey) {
    case 0xE0:
      hid_info(hdev, "Mapping G1!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[0]);
      return 1;
    case 0xE1:
      hid_info(hdev, "Mapping G2!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[1]);
      return 1;
    case 0xE2:
      hid_info(hdev, "Mapping G3!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[2]);
      return 1;
    case 0xE3:
      hid_info(hdev, "Mapping G4!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[3]);
      return 1;
    case 0xE4:
      hid_info(hdev, "Mapping G5!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[4]);
      return 1;
    case 0xE5:
      hid_info(hdev, "Mapping G6!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[5]);
      return 1;
    case 0xE6:
      hid_info(hdev, "Mapping G7!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[6]);
      return 1;
    case 0xE7:
      hid_info(hdev, "Mapping G8!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[7]);
      return 1;
    case 0xE8:
      hid_info(hdev, "Mapping G9!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[8]);
      return 1;
    case 0xE9:
      hid_info(hdev, "Mapping G10!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[9]);
      return 1;
    case 0xEA:
      hid_info(hdev, "Mapping G11!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[10]);
      return 1;
    case 0xEB:
      hid_info(hdev, "Mapping G12!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[11]);
      return 1;
    case 0xEC:
      hid_info(hdev, "Mapping G13!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[12]);
      return 1;
    case 0xED:
      hid_info(hdev, "Mapping G14!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[13]);
      return 1;
    case 0xEE:
      hid_info(hdev, "Mapping G15!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[14]);
      return 1;
    case 0xEF:
      hid_info(hdev, "Mapping G16!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[15]);
      return 1;
    case 0xF0:
      hid_info(hdev, "Mapping G17!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[16]);
      return 1;
    case 0xF1:
      hid_info(hdev, "Mapping G18!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[17]);
      return 1;
    case 0xF2:
      hid_info(hdev, "Mapping G19!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[18]);
      return 1;
    case 0xF3:
      hid_info(hdev, "Mapping G20!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[19]);
      return 1;
    case 0xF4:
      hid_info(hdev, "Mapping G21!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[20]);
      return 1;
    case 0xF5:
      hid_info(hdev, "Mapping G22!");
      hid_map_usage_clear(input, usage, bit, max, EV_KEY, g13_keycodes[21]);
      return 1;
    default:
      break;
  }

  return 0;
}

// TODO: Implement macro funcionality
static int g13_event(struct hid_device *hdev, struct hid_field *field, struct hid_usage *usage, __s32 value) {
  hid_info(hdev, "Event Caught!");
  return 0;
}
/*
 * Run when device is connected
 * TODO: Implment functionality to a create a custom keymap
 **/
static int g13_usb_probe(struct hid_device *hdev, const struct hid_device_id *id) {
  int ret = 0;
  //struct g13_drvdata *drvdata;
  //unsigned long quirks = id->driver_data;
  hid_info(hdev, "G13 Gamepad Connected!");
  
  /*
  drvdata = devm_kzalloc(&hdev->dev, sizeof(struct g13_drvdata), GFP_KERNEL);
	if (drvdata == NULL)
		return -ENOMEM;

	drvdata->quirks = quirks;
	hid_set_drvdata(hdev, drvdata);
  */

  ret = hid_parse(hdev);
  if(ret != 0) {
    hid_err(hdev, "Device Parsing Failed!");
    return ret;
  }

  ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
  if(ret != 0) {
    hid_err(hdev, "Failed to Start Device!");
    return ret;
  }
   
  return 0; // Device started successfully
}

/*
 * Run when device is disconnected
*/
static void g13_usb_remove(struct hid_device *hdev) {
  hid_info(hdev, "Gamepad Disconnected!");
  hid_hw_stop(hdev);
}


static const struct hid_device_id g13_usb_ids[] = {
  { HID_USB_DEVICE(0x046d, 0xc21c) }, // Logitech G13 Gamepad
  { } // Terminating Entry
}; 

MODULE_DEVICE_TABLE(hid, g13_usb_ids);

static struct hid_driver g13_usb_driver = {
  .name = "HID G13",
  .probe = g13_usb_probe,
  .remove = g13_usb_remove,
  .id_table = g13_usb_ids,
  .input_mapping = g13_input_mapping,
  .report_fixup = g13_report_fixup,
  //.event = g13_event,
};

module_hid_driver(g13_usb_driver);
