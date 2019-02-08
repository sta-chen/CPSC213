package arch.sm213.machine.student;

import machine.AbstractMainMemory;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class MainMemoryTest {
    private MainMemory myMemory;

    @Before
    public void beforeTest() {
        myMemory = new MainMemory(64);
    }

    @Test
    public void testIsAccessAligned() {
        // test for aligned
        assertTrue(myMemory.isAccessAligned(0, 1));
        assertTrue(myMemory.isAccessAligned(0, 4));
        assertTrue(myMemory.isAccessAligned(4, 4));
        assertTrue(myMemory.isAccessAligned(8, 4));

        //test for not aligned
        assertFalse(myMemory.isAccessAligned(3, 4));
        assertFalse(myMemory.isAccessAligned(5, 2));
        assertFalse(myMemory.isAccessAligned(17, 8));
    }

    @Test
    public void testBytesToInteger() {
        // test for zero
        assertEquals(0, myMemory.bytesToInteger((byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00));

        // test for positive integer
        assertEquals(1, myMemory.bytesToInteger((byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x01));
        assertEquals(305419896, myMemory.bytesToInteger((byte) 0x12, (byte) 0x34, (byte) 0x56, (byte) 0x78));

        // test for negative integer
        assertEquals(-1, myMemory.bytesToInteger((byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff));
        assertEquals(-1193047, myMemory.bytesToInteger((byte) 0xff, (byte) 0xed, (byte) 0xcb, (byte) 0xa9));
    }

    @Test
    public void testIntegerToBytes() {
        int testInteger1 = 0;
        int testInteger2 = 1;
        int testInteger3 = 305419896;
        int testInteger4 = -1;
        int testInteger5 = -1193047;

        byte[] expectedBytes1 = new byte[] {(byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00};
        byte[] expectedBytes2 = new byte[] {(byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x01};
        byte[] expectedBytes3 = new byte[] {(byte) 0x12, (byte) 0x34, (byte) 0x56, (byte) 0x78};
        byte[] expectedBytes4 = new byte[] {(byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
        byte[] expectedBytes5 = new byte[] {(byte) 0xff, (byte) 0xed, (byte) 0xcb, (byte) 0xa9};

        assertArrayEquals(expectedBytes1, myMemory.integerToBytes(testInteger1));
        assertArrayEquals(expectedBytes2, myMemory.integerToBytes(testInteger2));
        assertArrayEquals(expectedBytes3, myMemory.integerToBytes(testInteger3));
        assertArrayEquals(expectedBytes4, myMemory.integerToBytes(testInteger4));
        assertArrayEquals(expectedBytes5, myMemory.integerToBytes(testInteger5));
    }

    @Test
    public void testGetAndSet() {
        byte[] expectedBytes1 = new byte[]{(byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00};
        byte[] expectedBytes2 = new byte[]{(byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x01};
        byte[] expectedBytes3 = new byte[]{(byte) 0x12, (byte) 0x34, (byte) 0x56, (byte) 0x78};
        byte[] expectedBytes4 = new byte[]{(byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
        byte[] expectedBytes5 = new byte[]{(byte) 0xff, (byte) 0xed, (byte) 0xcb, (byte) 0xa9};

        // tests for set and get's functionality
        try {
            myMemory.set(0, expectedBytes1);
            assertArrayEquals(expectedBytes1, myMemory.get(0, expectedBytes1.length));
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("Catch an unexpected exception!");
        }

        try {
            myMemory.set(10, expectedBytes4);
            assertArrayEquals(expectedBytes4, myMemory.get(10, expectedBytes4.length));
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("Catch an unexpected exception!");
        }

        try {
            myMemory.set(30, expectedBytes5);
            assertArrayEquals(expectedBytes5, myMemory.get(30, expectedBytes5.length));
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("Catch an unexpected exception!");
        }

        // test for set, catching exception when address < 0
        try {
            myMemory.set(-1, expectedBytes2);
            fail("Doesn't catch the expected exception!");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            System.out.println("Catch the expected exception!");
        }

        // test for set, catching exception when out of boundary
        try {
            myMemory.set(1000, expectedBytes3);
            fail("Doesn't catch the expected exception!");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            System.out.println("Catch the expected exception!");
        }

        // test for get, catching exception when address < 0
        try {
            myMemory.get(-1, expectedBytes1.length);
            fail("Doesn't catch the expected exception!");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            System.out.println("Catch the expected exception!");
        }

        // test for get, catching exception when out of boundary
        try {
            myMemory.get(0, expectedBytes1.length + 1000);
            fail("Doesn't catch the expected exception!");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            System.out.println("Catch the expected exception!");
        }




    }




}