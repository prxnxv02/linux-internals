#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

// IRQ number for the keyboard (typically 1 on x86)
static int irq_number = 1;

// Interrupt handler function
static irqreturn_t my_keyboard_interrupt(int irq, void *dev_id)
{
    printk(KERN_INFO "Keyboard Interrupt: Key Press Detected!\n");
    return IRQ_HANDLED;
}

// Initialization function
static int __init my_interrupt_init(void)
{
    int result;
    
    // Register the interrupt handler
    result = request_irq(irq_number,                // IRQ number (keyboard is IRQ 1)
                         my_keyboard_interrupt,     // Interrupt handler function
                         IRQF_SHARED,               // Shared interrupt flag (most devices share interrupts)
                         "my_keyboard_interrupt",   // Name of the handler
                         (void *)(my_keyboard_interrupt)); // Device id (can be NULL)

    if (result) {
        printk(KERN_ERR "Failed to register IRQ %d\n", irq_number);
        return result;
    }

    printk(KERN_INFO "Keyboard Interrupt Handler Registered for IRQ %d\n", irq_number);
    return 0;
}

// Exit function (cleanup)
static void __exit my_interrupt_exit(void)
{
    // Free the IRQ
    free_irq(irq_number, (void *)(my_keyboard_interrupt));
    printk(KERN_INFO "Keyboard Interrupt Handler Unregistered from IRQ %d\n", irq_number);
}

module_init(my_interrupt_init);
module_exit(my_interrupt_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple hardware interrupt handler for keyboard IRQ");
