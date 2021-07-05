from unittest import TestCase

from src.markdown_element import MarkdownElement


class TestMarkdownElement(TestCase):
    def test_default_instance(self):
        me = MarkdownElement()
        self.assertEqual('', me.tag)
        self.assertEqual([], me.data)
        self.assertIsNone(None, me.parent)
        self.assertFalse(me.hidden)

    def test_nondefault_instance(self):
        me = MarkdownElement('tag', ['data'], hidden=True)
        self.assertEqual('tag', me.tag)
        self.assertEqual(['data'], me.data)
        self.assertTrue(me.hidden)

    def test_is_text_only_empty(self):
        me = MarkdownElement()
        self.assertFalse(me.is_text_only)

    def test_is_text_only_text_only(self):
        me = MarkdownElement(data=['stuff'])
        self.assertTrue(me.is_text_only)

    def test_is_text_only_has_tag(self):
        me = MarkdownElement('tag')
        self.assertFalse(me.is_text_only)

    def test_is_text_only_has_tag_and_text(self):
        me = MarkdownElement('tag', ['stuff'])
        self.assertFalse(me.is_text_only)

    def test_add_data(self):
        me = MarkdownElement('`', [])
        m2 = MarkdownElement('*', ['text', MarkdownElement('"', ['text2'])])

        me.add_data('text3')
        me.add_data(m2)

        expected = '`text3*text"text2"*`'
        actual = me.flatten()

        self.assertEqual(expected, actual)

    def test_parent_constructor(self):
        child = MarkdownElement('"', ['text2'])
        me = MarkdownElement('`', ['text ', child])
        self.assertEqual(me, child.parent)

    def test_parent_add_data(self):
        child = MarkdownElement('"', ['text2'])
        me = MarkdownElement('`', ['text '])
        me.add_data(child)
        self.assertEqual(me, child.parent)

    def test_tag_supports_list(self):
        me = MarkdownElement(['- ', '\n'], ['text'])
        expected = '- text\n'
        actual = me.flatten()
        self.assertEqual(expected, actual)

    def test_comparison_equal(self):
        me1 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        me2 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        self.assertEqual(me1, me2)

    def test_comparison_inequal_tag(self):
        me1 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        me2 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        me2.tag = ''
        self.assertNotEqual(me1, me2)

    def test_comparison_inequal_data_text(self):
        me1 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        me2 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        me2.data[0] = ''
        self.assertNotEqual(me1, me2)

    def test_comparison_inequal_data_element(self):
        me1 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        me2 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        me2.data[1].tag = ''
        self.assertNotEqual(me1, me2)

    def test_comparison_inequal_hidden(self):
        me1 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        me2 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        me2.hidden = True
        self.assertNotEqual(me1, me2)

    def test_comparison_inequal_parent(self):
        me1 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        me2 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        me2.parent = MarkdownElement()
        self.assertNotEqual(me1, me2)

    def test_comparison_inequal_nested_parent(self):
        me1 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        me2 = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        me2.data[1].parent = None
        self.assertNotEqual(me1, me2)

    def test_comparison_different_types(self):
        me = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        other = 1
        self.assertNotEqual(me, other)

    # These following tests test the flatten() function,
    # where n = the recursion depth of sub-elements within this one.
    def test_flatten_n1(self):
        me = MarkdownElement('`', ['text'])
        expected = '`text`'
        actual = me.flatten()
        self.assertEqual(expected, actual)

    def test_flatten_n2(self):
        me = MarkdownElement('`', ['text ', MarkdownElement('"', ['text2'])])
        expected = '`text "text2"`'
        actual = me.flatten()
        self.assertEqual(expected, actual)

    def test_str_calls_flatten(self):
        me = MarkdownElement('`', ['text ', MarkdownElement('"', ['text2'])])
        expected = '`text "text2"`'
        actual = str(me)
        self.assertEqual(expected, actual)

    def test_flatten_respects_hidden_n1(self):
        me = MarkdownElement('`', ['text'], hidden=True)
        expected = 'text'
        actual = me.flatten()
        self.assertEqual(expected, actual)

    def test_flatten_respects_hidden_n2(self):
        me = MarkdownElement('`', ['text ', MarkdownElement('*', ['text2'], hidden=True)])
        expected = '`text text2`'
        actual = me.flatten()
        self.assertEqual(expected, actual)
