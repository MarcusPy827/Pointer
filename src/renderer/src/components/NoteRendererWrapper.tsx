import { JSX } from 'react'
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter'
import { vs } from 'react-syntax-highlighter/dist/esm/styles/prism'
import Markdown from 'react-markdown'
import remarkGfm from 'remark-gfm'
import rehypeRaw from 'rehype-raw'
import remarkMath from 'remark-math'
import rehypeKatex from 'rehype-katex'

export default function NoteRenderer({ documentContent }): JSX.Element {
  return (
    <>
      <div className="note-renderer mdui-typo">
        <Markdown
          remarkPlugins={[remarkGfm, remarkMath]}
          rehypePlugins={[rehypeRaw, rehypeKatex]}
          children={documentContent}
          components={{
            code(props) {
              const { children, className, node, ...rest } = props
              const match = /language-(\w+)/.exec(className || '')
              return match ? (
                <SyntaxHighlighter
                  {...rest}
                  PreTag="div"
                  children={String(children).replace(/\n$/, '')}
                  language={match[1].toLocaleLowerCase()}
                  customStyle={{
                    backgroundColor: 'transparent',
                    border: 'none',
                    fontFamily:
                      '"Maple Mono", "LXGW WenKai Mono", "JetBrains Mono", "Ubuntu Sans Mono", "Ubuntu Mono", monospace'
                  }}
                  style={vs}
                />
              ) : (
                <code {...rest} className={className}>
                  {children}
                </code>
              )
            }
          }}
        />
      </div>
    </>
  )
}
