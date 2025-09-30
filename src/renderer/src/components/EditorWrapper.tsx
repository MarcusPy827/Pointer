import { Typography, Dropdown, MenuProps } from 'antd'
import { EditOutlined, CodeOutlined, EyeOutlined, CaretDownOutlined } from '@ant-design/icons'
import { JSX, useState } from 'react'
import { useTranslation } from 'react-i18next'
import NoteRenderer from './NoteRendererWrapper'
import MarkdownEditor from './MarkdownEditor'
import CodeEditor from './CodeEditorWrapper'

export default function EditorWrapper(): JSX.Element {
  const { t } = useTranslation()
  const [editorKey, setEditorKey] = useState<string>('1')
  const [documentContent, setDocumentContent] = useState<string>('')

  const editorWrapperList: MenuProps['items'] = [
    {
      key: '1',
      label: t('markdown_editor_desc'),
      icon: <EditOutlined />
    },
    {
      key: '2',
      label: t('code_editor_desc'),
      icon: <CodeOutlined />
    },
    {
      key: '3',
      label: t('markdown_renderer_desc'),
      icon: <EyeOutlined />
    }
  ]

  const onEditorSelectorClicked: MenuProps['onClick'] = ({ key }) => {
    setEditorKey(key)
  }

  const mapEditorKeyToJSX = (key: string): JSX.Element => {
    switch (key) {
      case '1':
        return (
          <div>
            <EditOutlined /> {t('markdown_editor_desc')}
          </div>
        )
        break
      case '2':
        return (
          <div>
            <CodeOutlined /> {t('code_editor_desc')}
          </div>
        )
        break
      case '3':
        return (
          <div>
            <EyeOutlined /> {t('markdown_renderer_desc')}
          </div>
        )
        break
      default:
        return <div>Unknown Editor</div>
    }
    return <div>Unknown Editor</div>
  }

  return (
    <>
      <div className="editor-toolbar">
        <div className="editor-toolbar-section">
          <Typography.Title level={3} className="no-select no-drag">
            {t('untitled_document')}
          </Typography.Title>
        </div>

        <div className="editor-toolbar-section">
          <Dropdown.Button
            type="primary"
            menu={{ items: editorWrapperList, onClick: onEditorSelectorClicked }}
            icon={<CaretDownOutlined />}
          >
            {mapEditorKeyToJSX(editorKey)}
          </Dropdown.Button>
        </div>
      </div>

      <div className="editor-area">
        {editorKey === '1' ? (
          <MarkdownEditor
            documentContent={documentContent}
            setDocumentContent={setDocumentContent}
          />
        ) : null}
        {editorKey === '2' ? (
          <CodeEditor documentContent={documentContent} setDocumentContent={setDocumentContent} />
        ) : null}
        {editorKey === '3' ? <NoteRenderer documentContent={documentContent} /> : null}
      </div>
    </>
  )
}
