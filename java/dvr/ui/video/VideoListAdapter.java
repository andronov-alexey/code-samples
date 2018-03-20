/*
* Creates and reuses views for video files.
*/

public class VideoListAdapter extends ArrayAdapter<VideoFileInfo> {
    private final IVideoItemListener m_listener;
    @Nullable
    private ISelectionProvider m_selectionProvider;
    @NonNull
    private List<VideoFileInfo> m_model;

    public interface IVideoItemListener {
        void onItemSelected(int _position);
        void onItemLockClicked(int _position);
        void onItemDeletePressed(int _position);
    }

    public VideoListAdapter(Context _context, @NonNull List<VideoFileInfo> _model, IVideoItemListener _listener) {
        super(_context, 0, _model);
        m_model = _model;
        m_listener = _listener;
    }

    private static class ViewHolder {
        final ImageView ivPreview;
        final TextView tvName;
        final TextView tvDuration;
        final TextView tvDate;
        final TextView tvSize;
        final CheckBox itemCheckBox;
        final ImageView lockButton;
        final ImageView deleteButton;

        ViewHolder(View _v) {
            ivPreview = (ImageView) _v.findViewById(R.id.ivVideoPreview);
            tvName = (TextView) _v.findViewById(R.id.tvName);
            tvDuration = (TextView) _v.findViewById(R.id.tvDuration);
            tvDate = (TextView) _v.findViewById(R.id.tvDate);
            tvSize = (TextView) _v.findViewById(R.id.tvFileSize);
            itemCheckBox = (CheckBox) _v.findViewById(R.id.cbVideoItemCheckBox);
            lockButton = (ImageView) _v.findViewById(R.id.ivLock_button);
            deleteButton = (ImageView) _v.findViewById(R.id.ivDelete_button);
        }
    }

    public void setSelectionProvider(ISelectionProvider _selectionProvider) {
        m_selectionProvider = _selectionProvider;
    }

    @NonNull
    @Override
    public View getView(int _position, View _convertView, @NonNull ViewGroup _parent) {
        ViewHolder holder;

        if (_convertView == null) {
            _convertView = LayoutInflater.from(getContext()).inflate(R.layout.video_library_list_item, _parent, false);
            holder = new ViewHolder(_convertView);
            _convertView.setTag(holder);
        } else {
            holder = (ViewHolder) _convertView.getTag();
        }

        VideoFileInfo videoItem = m_model.get(_position);

        if (videoItem != null) {
            if (videoItem.getURI() != null) {
                Picasso.with(holder.ivPreview.getContext())
                        .load(videoItem.getURI().toString())
                        .fit().centerCrop()
                        .placeholder(R.drawable.ic_video_preview_stub)
                        .into(holder.ivPreview)
                ;
            }

            holder.tvName.setText(videoItem.getFilename());
            holder.tvDuration.setText(FormatUtils.getReadableDuration(videoItem.getDuration()));
            holder.tvDate.setText(FormatUtils.getReadableDate(videoItem.getDateTaken().getTime()));
            holder.tvSize.setText(FormatUtils.getReadableFileSize(videoItem.getFileSize()));

            if (videoItem.isLocked()) {
                holder.lockButton.setImageResource(R.drawable.ic_lock);
            } else {
                holder.lockButton.setImageResource(R.drawable.ic_lock_open);
            }
        }

        final int position = _position;

        if (m_selectionProvider != null) {
            holder.itemCheckBox.setChecked(m_selectionProvider.getSelectedPositions().contains(_position));
        }

        holder.itemCheckBox.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                m_listener.onItemSelected(position);
            }
        });

        holder.lockButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                m_listener.onItemLockClicked(position);
            }
        });

        holder.deleteButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                m_listener.onItemDeletePressed(position);
            }
        });

        return _convertView;
    }

    @Override
    public int getCount() {
        return m_model.size();
    }

    @UiThread
    public void setVideos(List<VideoFileInfo> _model) {
        m_model = _model;

        notifyDataSetChanged();
    }
}
